#include "plane.h"

#include "osg/Texture2D"
#include "osg_tools.h"
#include "osgDB/ReadFile"

namespace vis
{
	plane::plane( float xw, float zw, const xo::path& image )
	{
		float hxw = xw / 2.0f;
		float hzw = zw / 2.0f;

		osg::ref_ptr<osg::Image> testImage = osgDB::readImageFile( image.str() );
		xo_assert( testImage.valid() );

		int iw = testImage->s();
		int ih = testImage->t();

		osg::ref_ptr<osg::Texture2D> testTexture = new osg::Texture2D;
		testTexture->setImage( testImage );
		testTexture->setWrap( osg::Texture::WRAP_S, osg::Texture::REPEAT );
		testTexture->setWrap( osg::Texture::WRAP_T, osg::Texture::REPEAT );
		testTexture->setMaxAnisotropy( 8.0f );

		osg::ref_ptr<osg::Geometry> geom = osg::createTexturedQuadGeometry(
			osg::Vec3( 0.0f, hxw, hzw ),
			osg::Vec3( 0.0f, -xw, 0.0f ),
			osg::Vec3( 0.0f, 0.0f, -zw ), 0, 0, xw / 2, zw / 2 );

		geom->getOrCreateStateSet()->setTextureAttributeAndModes( 0, testTexture.get() );
		geom->getOrCreateStateSet()->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
		geom->setCullingActive( true );

		osg::ref_ptr<osg::Geode> geode = new osg::Geode();
		geode->getOrCreateStateSet()->setMode( GL_CULL_FACE, osg::StateAttribute::ON );
		set_shadow_mask( geode, true, false );

		geode->addDrawable( geom );

		osg::Material* mat = new osg::Material;
		mat->setColorMode( osg::Material::EMISSION );
		mat->setSpecular( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		mat->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		mat->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		geode->getOrCreateStateSet()->setAttribute( mat );

		node->addChild( geode );
	}

	plane::plane( int x_tiles, int z_tiles, float tile_size, color a, color b )
	{
		// fill in vertices for grid, note numTilesX+1 * numTilesY+1...
		osg::Vec3Array* coords = new osg::Vec3Array;
		for ( int z = 0; z <= z_tiles; ++z )
		{
			for ( int x = 0; x <= x_tiles; ++x )
				coords->push_back( -osg::Vec3( ( x - x_tiles / 2 ) * tile_size, 0, -( z - z_tiles / 2 ) * tile_size ) );
		}

		//Just two colors - gray and grey
		osg::Vec4Array* colors = new osg::Vec4Array;
		colors->push_back( make_osg( a ) ); // white
		colors->push_back( make_osg( b ) ); // black

		osg::ref_ptr<osg::DrawElementsUShort> whitePrimitives = new osg::DrawElementsUShort( GL_QUADS );
		osg::ref_ptr<osg::DrawElementsUShort> blackPrimitives = new osg::DrawElementsUShort( GL_QUADS );

		int numIndicesPerRow = x_tiles + 1;
		for ( int iz = 0; iz < z_tiles; ++iz )
		{
			for ( int ix = 0; ix < x_tiles; ++ix )
			{
				osg::DrawElementsUShort* primitives = ( ( iz + ix ) % 2 == 0 ) ? whitePrimitives.get() : blackPrimitives.get();
				primitives->push_back( ix + ( iz + 1 )*numIndicesPerRow );
				primitives->push_back( ix + iz * numIndicesPerRow );
				primitives->push_back( ( ix + 1 ) + iz * numIndicesPerRow );
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

		osg::Material* mat = new osg::Material;
		mat->setColorMode( osg::Material::EMISSION );
		mat->setSpecular( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		mat->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		mat->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4( 0, 0, 0, 0 ) );
		geode->getOrCreateStateSet()->setAttribute( mat );

		set_shadow_mask( geode, true, false );

		node->addChild( geode );
	}
}
