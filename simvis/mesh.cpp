#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"

namespace simvis
{

	mesh::mesh( const string& filename )
	{
		node = new osg::PositionAttitudeTransform;
		auto mesh = osgDB::readNodeFile( filename );
		node->addChild( mesh );
	}

	mesh::mesh( primitive_shape shape, const vec3f& dim, const vec4f& color, float detail )
	{
		node = new osg::PositionAttitudeTransform;

		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd;

		switch ( shape )
		{
		case primitive_shape::sphere:
			sd = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), dim.length() ), hints );
			break;
		case primitive_shape::box:
			break;
		case primitive_shape::cylinder_x:
			break;
		case primitive_shape::cylinder_y:
			break;
		case primitive_shape::cylinder_z:
			break;
		}

		sd->setColor( make_osg( color ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		
		node->addChild( g );
	}

	void mesh::pos( const vec3f& pos )
	{
		node->setPosition( make_osg( pos ) );
	}

	void mesh::ori( const quatf& ori )
	{
		node->setAttitude( make_osg( ori ) );
	}
}
