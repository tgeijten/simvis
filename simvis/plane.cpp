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
			osg::Vec3( -hxw, 0.0f, hzw ),
			osg::Vec3( xw, 0.0f, 0.0f ),
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
}
