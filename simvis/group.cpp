#include "group.h"
#include "mesh.h"
#include "arrow.h"
#include "path.h"
#include "osg_tools.h"

namespace vis
{
	group::group()
	{
		node = new osg::PositionAttitudeTransform;
	}

	mesh group::add_mesh( const string& filename )
	{
		return mesh( *this, filename );
	}

	mesh group::add_sphere( float radius, color c, float detail )
	{
		return mesh( *this, primitive_shape::sphere, vec3f( radius, 0, 0 ), c, detail );
	}

	mesh group::add_cube( vec3f dim, color c )
	{
		return mesh( *this, primitive_shape::box, dim, c );
	}

	mesh group::add_cylinder( float radius, float height, color c, float detail )
	{
		return mesh( *this, primitive_shape::cylinder, vec3f( radius, 0, height ), c, detail );
	}

	vis::mesh group::add_cone( float radius, float height, color c, float detail )
	{
		return mesh( *this, primitive_shape::cone, vec3f( radius, 0, height ), c, detail );
	}

	arrow group::add_arrow( float radius, color c, float detail )
	{
		return arrow( *this, radius, c, detail );
	}

	path group::add_path( size_t num_points, float radius, color c, float detail /*= 0.5f */ )
	{
		return path( *this, num_points, radius, c, detail );
	}

	void group::attach( object& o )
	{
		node->addChild( o.osg_node() );
	}

	void group::detach( object& o )
	{
		node->removeChild( o.osg_node() );
	}

	void group::detach_all()
	{
		node->removeChildren( 0, node->getNumChildren() );
	}

	size_t group::size()
	{
		return node->getNumChildren();
	}

	void group::transform( const transformf& t )
	{
		static_cast< osg::PositionAttitudeTransform& >( *node ).setPosition( make_osg( t.p ) );
		static_cast< osg::PositionAttitudeTransform& >( *node ).setAttitude( make_osg( t.q ) );
	}

}
