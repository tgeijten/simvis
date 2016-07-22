#include "stdafx.h"
#include "light.h"
#include "osg_tools.h"
#include "scene.h"

namespace vis
{
	int light::unique_light_number = 0;

	light::light( scene& s, const vec3f& pos, const color& col )
	{
		auto l = new osg::Light;
		l->setLightNum( unique_light_number++ );

		l->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
		l->setDiffuse( make_osg( col ) );
		l->setSpecular( osg::Vec4( 1, 1, 1, 1 ) );
		l->setAmbient( osg::Vec4( 1, 1, 1, 1 ) );

		light_source = new osg::LightSource;
		light_source->setLight( l );
		light_source->setLocalStateSetModes( osg::StateAttribute::ON );

		s.osg_group().addChild( light_source );
		s.osg_group().getOrCreateStateSet()->setMode( GL_LIGHT0 + get_number(), osg::StateAttribute::ON );
	}
}
