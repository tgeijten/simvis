#include "scene.h"

#include "osgShadow/ShadowedScene"
#include "osgShadow/SoftShadowMap"
#include "osg_tools.h"

namespace vis
{
	scene::scene()
	{
		auto s_root = new osgShadow::ShadowedScene;
		root = s_root;

		/// setup shadows
		auto sm = new osgShadow::ShadowMap;
		sm->setTextureSize( osg::Vec2s( 1024, 1024 ) );
        s_root->setShadowTechnique( sm );

		auto ss = new osgShadow::ShadowSettings;
		ss->setCastsShadowTraversalMask( OsgCastShadowMask );
		ss->setReceivesShadowTraversalMask( OsgReceiveShadowMask ); // this one doesn't do anything in osg
		s_root->setShadowSettings( ss );

		// create floor
		auto ground = create_tile_floor( 64, 64, 1 );
		set_shadow_mask( ground, true, false );
		root->addChild( ground );
	}

	scene::~scene() {}

	mesh scene::make_mesh( const string& filename )
	{
		mesh m( filename );
		attach( m );
		return m;
	}

	mesh scene::make_sphere( float radius, color c, float detail )
	{
		return mesh( *this, primitive_shape::sphere, vec3f( radius, 0, 0 ), c, detail );
	}

	mesh scene::make_cube( vec3f dim, color c )
	{
		return mesh( *this, primitive_shape::box, dim, c );
	}

	mesh scene::make_cylinder( float radius, float height, color c, float detail )
	{
		return mesh( *this, primitive_shape::cylinder, vec3f( radius, 0, height ), c, detail );
	}

	vis::mesh scene::make_cone( float radius, float height, color c, float detail )
	{
		return mesh( *this, primitive_shape::cone, vec3f( radius, 0, height ), c, detail );
	}

	arrow scene::make_arrow( float radius, color c, float detail )
	{
		return arrow( *this, radius, c, detail );
	}

	path scene::make_path( float radius, color c, float detail )
	{
		return path();
	}

	vis::light scene::make_light( const vec3f& pos, const color& c )
	{
		light l( pos, c );
		root->addChild( l.osg_node() );
		root->getOrCreateStateSet()->setMode( GL_LIGHT0 + l.get_number(), osg::StateAttribute::ON );
		return l;
	}

	void scene::attach( object& o )
	{
		root->addChild( o.osg_node() );
	}

	void scene::detach( object& o )
	{
		root->removeChild( o.osg_node() );
	}
}
