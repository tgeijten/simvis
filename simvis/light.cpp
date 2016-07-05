#include "light.h"
#include "osg_tools.h"

namespace simvis
{
	int light::unique_light_number = 0;

	light::light( const vec3f& pos, const color& col )
	{
		auto l = new osg::Light;
		l->setLightNum( ++unique_light_number );
		l->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
		l->setDiffuse( make_osg( col ) );
		l->setSpecular( osg::Vec4( 1, 1, 1, 1 ) );

		light_source = new osg::LightSource;
		light_source->setLight( l );
		light_source->setLocalStateSetModes( osg::StateAttribute::ON );
	}
}
