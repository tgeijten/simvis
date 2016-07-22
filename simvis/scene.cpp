#include "stdafx.h"
#include "scene.h"

#include "osgShadow/ShadowedScene"
#include "osgShadow/SoftShadowMap"
#include "osg_tools.h"

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

		// create floor
		auto ground = create_tile_floor( 64, 64, 1 );
		set_shadow_mask( ground, true, false );
		node->addChild( ground );
	}

	scene::~scene() {}

	vis::light scene::add_light( const vec3f& pos, const color& c )
	{
		return light( *this, pos, c );
	}
}
