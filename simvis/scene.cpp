#include "scene.h"

#include "osgShadow/ShadowedScene"
#include "osgShadow/SoftShadowMap"
#include "osg_tools.h"
#include "osgDB/ObjectCache"
#include "osgDB/ReadFile"

namespace vis
{
	scene::scene( bool use_shadows )
	{
		if ( use_shadows )
		{
			auto s_root = new osgShadow::ShadowedScene;
			node = s_root;

			/// setup shadows
			auto sm = new osgShadow::SoftShadowMap;
			sm->setTextureSize( osg::Vec2s( 1024, 1024 ) );
			s_root->setShadowTechnique( sm );
			//sm->setAmbientBias( osg::Vec2( 0.5f, 0.5f ) );

			auto ss = new osgShadow::ShadowSettings;
			ss->setCastsShadowTraversalMask( OsgCastShadowMask );
			ss->setReceivesShadowTraversalMask( OsgReceiveShadowMask ); // this one doesn't do anything in osg
			s_root->setShadowSettings( ss );
		}
		else
		{
			node = new osg::Group;
		}

		// enable lighting
		node->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::ON );

		// set default lighting
		osg::ref_ptr< osg::Material > mat = new osg::Material;
		mat->setDiffuse( osg::Material::FRONT, osg::Vec4( 1, 1, 1, 1 ) );
		mat->setSpecular( osg::Material::FRONT, osg::Vec4( 1, 1, 1, 1 ) );
		mat->setAmbient( osg::Material::FRONT, osg::Vec4( 1, 1, 1, 1 ) );
		mat->setEmission( osg::Material::FRONT, osg::Vec4( 0, 0, 0, 1 ) );
		mat->setShininess( osg::Material::FRONT, 25.0 );
		mat->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
		node->getOrCreateStateSet()->setAttribute( mat );
	}

	void scene::create_tile_floor( int x_width, int z_width, int tile_size, color a, color b )
	{
		// create floor
		auto ground = vis::create_tile_floor( x_width, z_width, tile_size, a, b );
		set_shadow_mask( ground, true, false );
		node->addChild( ground );
	}

	void scene::create_textured_floor( int xw, int zw, const xo::path& image )
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

	scene::~scene() {}

	vis::light scene::add_light( const vec3f& pos, const color& c )
	{
		return light( *this, pos, c );
	}
}
