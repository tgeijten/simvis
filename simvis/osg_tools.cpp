#include "osg_tools.h"

#include <osg/Geometry>
#include "osg/Material"
#include "flut/prop_node.hpp"
#include "flut/system/log.hpp"

using namespace flut;

namespace vis
{
	osg::Geode* create_tile_floor( int x_tiles, int z_tiles, float tile_width /*= 1.0f */ )
	{
		// fill in vertices for grid, note numTilesX+1 * numTilesY+1...
		osg::Vec3Array* coords = new osg::Vec3Array;
		for ( int z = 0; z <= z_tiles; ++z )
		{
			for ( int x = 0; x <= x_tiles; ++x )
				coords->push_back( -osg::Vec3( ( x - x_tiles / 2 ) * tile_width, 0, -( z - z_tiles / 2 ) * tile_width ) );
		}

		//Just two colors - gray and grey
		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back( osg::Vec4( 0.6f, 0.6f, 0.6f, 1.0f ) ); // white
		colors->push_back( osg::Vec4( 0.5f, 0.5f, 0.5f, 1.0f ) ); // black

		osg::ref_ptr<osg::DrawElementsUShort> whitePrimitives = new osg::DrawElementsUShort( GL_QUADS );
		osg::ref_ptr<osg::DrawElementsUShort> blackPrimitives = new osg::DrawElementsUShort( GL_QUADS );

		int numIndicesPerRow = x_tiles + 1;
		for ( int iz = 0; iz < z_tiles; ++iz )
		{
			for ( int ix = 0; ix < x_tiles; ++ix )
			{
				osg::DrawElementsUShort* primitives = ( ( iz + ix ) % 2 == 0 ) ? whitePrimitives.get() : blackPrimitives.get();
				primitives->push_back( ix + ( iz + 1 )*numIndicesPerRow );
				primitives->push_back( ix + iz*numIndicesPerRow );
				primitives->push_back( ( ix + 1 ) + iz*numIndicesPerRow );
				primitives->push_back( ( ix + 1 ) + ( iz + 1 )*numIndicesPerRow );
			}
		}

		// set up a single normal
		osg::Vec3Array* normals = new osg::Vec3Array;
		normals->push_back( osg::Vec3( 0.0f, 1.0f, 0.0f ) );

		osg::Geometry* geom = new osg::Geometry;
		geom->setVertexArray( coords );
		geom->setColorArray( colors, osg::Array::BIND_PER_PRIMITIVE_SET );
		geom->setNormalArray( normals, osg::Array::BIND_OVERALL );
		geom->setCullingActive( true );

		geom->addPrimitiveSet( whitePrimitives.get() );
		geom->addPrimitiveSet( blackPrimitives.get() );
		osg::Geode* geode = new osg::Geode;
		geode->addDrawable( geom );
		geode->getOrCreateStateSet()->setMode( GL_CULL_FACE, osg::StateAttribute::ON );

		return geode;
	}

	SIMVIS_API osg::ref_ptr< osg::Geode > read_vtp( const string& filename )
	{
		prop_node root_pn = read_xml( filename );
		prop_node& poly_pn = root_pn[ "VTKFile" ][ "PolyData" ][ "Piece" ];
		auto point_count = poly_pn.get< int >( "NumberOfPoints");
		auto poly_count = poly_pn.get< int >( "NumberOfPolys" );
		//auto& normals_pn = poly_pn[ "PointData" ][ "DataArray" ];
		//auto& points_pn = poly_pn[ "Points" ][ "DataArray" ];
		//auto& poly_con_pn = poly_pn[ "Polys" ][ 0 ];
		//auto& poly_ofs_pn = poly_pn[ "Polys" ][ 1 ];

		// create normal array
		osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array( point_count );
		{
			std::stringstream str( poly_pn[ "PointData" ][ "DataArray" ].get_value() );
			for ( int idx = 0; idx < point_count; ++idx )
				str >> normals->at( idx ).x() >> normals->at( idx ).y() >> normals->at( idx ).z();
		}

		// create Geometry object to store all the vertices and lines primitive.
		osg::Geometry* polyGeom = new osg::Geometry();
		osg::Vec3Array* vertices = new osg::Vec3Array( point_count );
		{
			std::stringstream str( poly_pn[ "Points" ][ "DataArray" ].get_value() );
			for ( int idx = 0; idx < point_count; ++idx )
				str >> vertices->at( idx ).x() >> vertices->at( idx ).y() >> vertices->at( idx ).z();
		}

		osg::ref_ptr< osg::DrawElementsUShort > trianglePrimitives = new osg::DrawElementsUShort( GL_TRIANGLES );
		osg::ref_ptr< osg::DrawElementsUShort > quadPrimitives = new osg::DrawElementsUShort( GL_QUADS );

		{
			auto con_vec = from_vec_str< unsigned short >( poly_pn[ "Polys" ][ 0 ].get_value() );
			auto ofs_vec = from_vec_str< unsigned short >( poly_pn[ "Polys" ][ 1 ].get_value() );
			
			//for ( auto& ofs : con_vec )
			//	trianglePrimitives->push_back( ofs );

			for ( size_t idx = 0; idx < ofs_vec.size(); ++idx )
			{
				auto end_ofs = ofs_vec[ idx ];
				auto begin_ofs = idx == 0 ? unsigned short( 0 ) : ofs_vec[ idx - 1 ];
				auto num_ver = end_ofs - begin_ofs;
				if ( num_ver == 3 )
				{
					trianglePrimitives->push_back( con_vec[begin_ofs] );
					trianglePrimitives->push_back( con_vec[begin_ofs + 1] );
					trianglePrimitives->push_back( con_vec[begin_ofs + 2] );
				}
				else if ( num_ver == 4 )
				{
					quadPrimitives->push_back( con_vec[begin_ofs] );
					quadPrimitives->push_back( con_vec[begin_ofs + 1] );
					quadPrimitives->push_back( con_vec[begin_ofs + 2] );
					quadPrimitives->push_back( con_vec[begin_ofs + 3] );
				}
				else
				{
					// silently ignore...
					//flut::log::warning( "Unknown primitive type, number of vertices = ", num_ver );
				}
			}
		}

		// add primitives
		if ( trianglePrimitives->size() > 0 )
			polyGeom->addPrimitiveSet( trianglePrimitives );
		if ( quadPrimitives->size() > 0 )
			polyGeom->addPrimitiveSet( quadPrimitives );

		// create color array (shared)
		//osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		//shared_colors->push_back(osg::Vec4(1.0f,0.0f,0.0f,1.0f));
		//polyGeom->setColorArray( shared_colors.get(), osg::Array::BIND_OVERALL );

		// pass the created vertex array to the points geometry object
		polyGeom->setVertexArray( vertices );
		polyGeom->setNormalArray( normals, osg::Array::BIND_PER_VERTEX );
		polyGeom->setCullingActive( true );

		// add the points geometry to the geode.
		osg::ref_ptr< osg::Geode > geode = new osg::Geode;
		geode->addDrawable(polyGeom);
		geode->getOrCreateStateSet()->setMode( GL_CULL_FACE, osg::StateAttribute::ON );

		return geode;
	}

	void set_shadow_mask( osg::Node* n, bool receive, bool cast )
	{
		n->setNodeMask( receive ? n->getNodeMask() | OsgReceiveShadowMask : n->getNodeMask() & ~OsgReceiveShadowMask );
		n->setNodeMask( cast ? n->getNodeMask() | OsgCastShadowMask : n->getNodeMask() & ~OsgCastShadowMask );
	}
}
