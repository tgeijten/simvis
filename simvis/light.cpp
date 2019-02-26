#include "light.h"
#include "osg_tools.h"
#include "scene.h"

namespace vis
{
	int light::unique_light_number = 0;

	light::light( node& parent, const vec3f& pos, const color& col ) :
	node( &parent )
	{
		auto l = new osg::Light;
		l->setLightNum( unique_light_number++ );

		l->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
		l->setDiffuse( to_osg( col ) );
		l->setSpecular( osg::Vec4( 1, 1, 1, 1 ) );
		l->setAmbient( osg::Vec4( 1, 1, 1, 1 ) );

		light_source = new osg::LightSource;
		light_source->setLight( l );
		light_source->setLocalStateSetModes( osg::StateAttribute::ON );
		light_source->setReferenceFrame( osg::LightSource::RELATIVE_RF );

		osg_group().addChild( light_source );
		parent.osg_group().getOrCreateStateSet()->setMode( GL_LIGHT0 + get_number(), osg::StateAttribute::ON );
	}

	void light::pos( const vec3f& pos )
	{
		light_source->getLight()->setPosition( osg::Vec4f( pos.x, pos.y, pos.z, 1 ) );
	}

	void light::attenuation( float c, float l, float q )
	{
		light_source->getLight()->setConstantAttenuation( c );
		light_source->getLight()->setLinearAttenuation( l );
		light_source->getLight()->setQuadraticAttenuation( q );
	}
}
