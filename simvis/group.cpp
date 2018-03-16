#include "group.h"
#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "osg_tools.h"
#include "axes.h"

namespace vis
{
	group::group()
	{
		node = new osg::PositionAttitudeTransform;
	}

	mesh group::add_mesh( const path& filename )
	{
		mesh m( filename );
		attach( m );
		return m;
	}

	mesh group::add_sphere( float radius, color c, float detail )
	{
		mesh m( primitive_shape::sphere, vec3f( radius, 0, 0 ), c, detail );
		attach( m );
		return m;
	}

	mesh group::add_cube( vec3f dim, color c )
	{
		mesh m( primitive_shape::box, dim, c );
		attach( m );
		return m;
	}

	mesh group::add_cylinder( float radius, float height, color c, float detail )
	{
		mesh m( primitive_shape::cylinder, vec3f( radius, 0, height ), c, detail );
		attach( m );
		return m;
	}

	vis::mesh group::add_capsule( float radius, float height, color c, float detail )
	{
		mesh m( primitive_shape::capsule, vec3f( radius, 0, height ), c, detail );
		attach( m );
		return m;
	}

	vis::mesh group::add_cone( float radius, float height, color c, float detail )
	{
		mesh m( primitive_shape::cone, vec3f( radius, 0, height ), c, detail );
		attach( m );
		return m;
	}

	arrow group::add_arrow( float radius, float head_radius, color c, float detail )
	{
		arrow m( radius, head_radius, c, detail );
		attach( m );
		return m;
	}

	axes group::add_axes( vec3f length, float detail /*= 0.5f */ )
	{
		axes a( length, detail );
		attach( a );
		return a;
	}

	trail group::add_trail( size_t num_points, float radius, color c, float detail /*= 0.5f */ )
	{
		trail t( num_points, radius, c, detail );
		attach( t );
		return t;
	}

	group group::add_group()
	{
		group g;
		attach( g );
		return g;
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

	group& group::transform( const transformf& t )
	{
		static_cast< osg::PositionAttitudeTransform& >( *node ).setPosition( make_osg( t.p ) );
		static_cast< osg::PositionAttitudeTransform& >( *node ).setAttitude( make_osg( t.q ) );
		return *this;
	}
}
