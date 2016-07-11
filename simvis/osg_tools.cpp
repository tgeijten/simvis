#include "osg_tools.h"

#include <osg/Geometry>
#include "osg/Material"

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
		colors->push_back( osg::Vec4( 0.4f, 0.4f, 0.4f, 1.0f ) ); // black

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
		osg::ref_ptr< osg::Geode > geode = new osg::Geode;
		// now we'll stop creating separate normal and color arrays
		// since we are using the same values all the time, we'll just
		// share the same ColorArray and NormalArrays..

		// set the colors as before, use a ref_ptr rather than just
		// standard C pointer, as that in the case of it not being
		// assigned it will still be cleaned up automatically.
		osg::ref_ptr<osg::Vec4Array> shared_colors = new osg::Vec4Array;
		shared_colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));

		// same trick for shared normal.
		osg::ref_ptr<osg::Vec3Array> shared_normals = new osg::Vec3Array;
		shared_normals->push_back(osg::Vec3(0.0f,-1.0f,0.0f));



		// Note on vertex ordering.
		// According to the OpenGL diagram vertices should be specified in a clockwise direction.
		// In reality you need to specify coords for polygons in a anticlockwise direction
		// for their front face to be pointing towards you; get this wrong and you could
		// find back face culling removing the wrong faces of your models.  The OpenGL diagram
		// is just plain wrong, but it's a nice diagram so we'll keep it for now!

		// create POLYGON
		{
			// create Geometry object to store all the vertices and lines primitive.
			osg::Geometry* polyGeom = new osg::Geometry();

			// this time we'll use C arrays to initialize the vertices.
			// note, anticlockwise ordering.
			// note II, OpenGL polygons must be convex, planar polygons, otherwise
			// undefined results will occur.  If you have concave polygons or ones
			// that cross over themselves then use the osgUtil::Tessellator to fix
			// the polygons into a set of valid polygons.
			osg::Vec3 myCoords[] =
			{
				osg::Vec3(-1.0464, 0.0f, -0.193626),
				osg::Vec3(-1.0258, 0.0f, -0.26778),
				osg::Vec3(-0.807461, 0.0f, -0.181267),
				osg::Vec3(-0.766264, 0.0f, -0.0576758),
				osg::Vec3(-0.980488, 0.0f, -0.094753)
			};

			int numCoords = sizeof(myCoords)/sizeof(osg::Vec3);

			osg::Vec3Array* vertices = new osg::Vec3Array(numCoords,myCoords);

			// pass the created vertex array to the points geometry object.
			polyGeom->setVertexArray(vertices);

			// use the shared color array.
			polyGeom->setColorArray(shared_colors.get(), osg::Array::BIND_OVERALL);


			// use the shared normal array.
			polyGeom->setNormalArray(shared_normals.get(), osg::Array::BIND_OVERALL);


			// This time we simply use primitive, and hardwire the number of coords to use
			// since we know up front,
			polyGeom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POLYGON,0,numCoords));

			// add the points geometry to the geode.
			geode->addDrawable(polyGeom);
		}

		return geode;
	}

	void set_shadow_mask( osg::Node* n, bool receive, bool cast )
	{
		n->setNodeMask( receive ? n->getNodeMask() | OsgReceiveShadowMask : n->getNodeMask() & ~OsgReceiveShadowMask );
		n->setNodeMask( cast ? n->getNodeMask() | OsgCastShadowMask : n->getNodeMask() & ~OsgCastShadowMask );
	}
}
