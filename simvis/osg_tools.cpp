#include "osg_tools.h"

#include <osg/Geometry>

namespace simvis
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

	void set_shadow_mask( osg::Node* n, bool receive, bool cast )
	{
		n->setNodeMask( receive ? n->getNodeMask() | OsgReceiveShadowMask : n->getNodeMask() & ~OsgReceiveShadowMask );
		n->setNodeMask( cast ? n->getNodeMask() | OsgCastShadowMask : n->getNodeMask() & ~OsgCastShadowMask );
	}

}
