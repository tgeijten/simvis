#include "group.h"
#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "osg_tools.h"
#include "axes.h"
#include "xo/geometry/shape.h"

namespace vis
{
	using xo::shape;
	using xo::shape_type;

	group::group()
	{
		node_ = new osg::PositionAttitudeTransform;
	}

	group::~group()
	{
		release();
	}

	mesh group::add_mesh( const xo::path& filename )
	{
		mesh m( filename );
		attach( m );
		return m;
	}

	mesh group::add_sphere( float radius, color c, float detail )
	{
		mesh m( shape( shape_type::sphere, radius ), c, detail );
		attach( m );
		return m;
	}

	mesh group::add_cube( vec3f dim, color c )
	{
		mesh m( shape( shape_type::box, dim.x, dim.y, dim.z ), c );
		attach( m );
		return m;
	}

	mesh group::add_cylinder( float radius, float height, color c, float detail )
	{
		mesh m( shape( shape_type::cylinder, radius, height ), c, detail );
		attach( m );
		return m;
	}

	vis::mesh group::add_capsule( float radius, float height, color c, float detail )
	{
		mesh m( shape( shape_type::capsule, radius, height ), c, detail );
		attach( m );
		return m;
	}

	vis::mesh group::add_cone( float radius, float height, color c, float detail )
	{
		mesh m( shape( shape_type::cone, radius, height ), c, detail );
		attach( m );
		return m;
	}

	arrow group::add_arrow( float radius, float head_radius, color c, float detail )
	{
		arrow m( radius, head_radius, c, detail );
		attach( m );
		return m;
	}

	axes group::add_axes( vec3f length, float detail )
	{
		axes a( length, detail );
		attach( a );
		return a;
	}

	trail group::add_trail( size_t num_points, float radius, color c, float detail )
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
		node_->addChild( o.osg_node() );
	}

	void group::detach( object& o )
	{
		node_->removeChild( o.osg_node() );
	}

	void group::detach_all()
	{
		node_->removeChildren( 0, node_->getNumChildren() );
	}

	void group::release()
	{
		if ( node_ && node_->referenceCount() == node_->getNumParents() + 1 )
		{
			// this is the last ref, so remove from all parents
			while ( node_->getNumParents() > 0 )
				node_->getParent( 0 )->removeChild( node_ );
		}
	}

	size_t group::size()
	{
		return node_->getNumChildren();
	}

	void group::transform( const transformf& t )
	{
		static_cast< osg::PositionAttitudeTransform& >( *node_ ).setPosition( make_osg( t.p ) );
		static_cast< osg::PositionAttitudeTransform& >( *node_ ).setAttitude( make_osg( t.q ) );
	}

	void group::pos( const vec3f& p )
	{
		static_cast<osg::PositionAttitudeTransform&>( *node_ ).setPosition( make_osg( p ) );
	}

	void group::ori( const quatf& q )
	{
		static_cast<osg::PositionAttitudeTransform&>( *node_ ).setAttitude( make_osg( q ) );
	}
}
