#pragma once

#include "object.h"
#include <osg/PositionAttitudeTransform>
#include "xo/geometry/vec3_type.h"
#include "xo/geometry/quat_type.h"

namespace vis
{
	class SIMVIS_API group : public object
	{
	public:
		group();
		group( const group& other ) : node_( other.node_ ) {}
		group& operator=( const group& other ) { node_ = other.node_; return *this; }
		virtual ~group();

		mesh add_mesh( const xo::path& filename );
		mesh add_sphere( float radius, color c, float detail = 0.5f );
		mesh add_cube( vec3f dim, color c );
		mesh add_cylinder( float radius, float height, color c, float detail = 0.5f );
		mesh add_capsule( float radius, float height, color c, float detail = 0.5f );
		mesh add_cone( float radius, float height, color c, float detail = 0.5f );
		arrow add_arrow( float radius, float head_radius, color c, float detail = 0.5f );
		axes add_axes( vec3f length, float detail = 0.5f );
		trail add_trail( size_t num_points, float radius, color c, float detail = 0.5f );
		group add_group();

		template< typename T, typename... Args > T add( Args&&... a ) { T o( std::forward< Args >( a )... ); attach( o ); return o; }

		void attach( object& o );
		template< typename... Args > void attach( object& o, Args&... args ) { attach( o ); attach( args... ); }

		void detach( object& o );
		void detach_all();
		void release();

		size_t size();

		virtual osg::Node* osg_node() override { return node_; }
		osg::Group& osg_group() { return *node_; }
		osg::PositionAttitudeTransform& osg_trans_node() { return static_cast<osg::PositionAttitudeTransform&>( *node_ ); }

		virtual void transform( const transformf& t ) override;
		virtual void pos( const vec3f& p ) override;
		virtual void ori( const quatf& q ) override;

	protected:
		osg::ref_ptr< osg::Group > node_;
	};
}
