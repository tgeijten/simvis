#pragma once

#include "object.h"
#include <osg/PositionAttitudeTransform>
#include "xo/geometry/vec3_type.h"
#include "xo/geometry/quat_type.h"
#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

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
		mesh add_shape( const xo::shape& s, color c, float detail = 0.05f );
		arrow add_arrow( float radius, float head_radius, color c, float detail = 0.5f );
		axes add_axes( vec3f length, float detail = 0.5f );
		trail add_trail( size_t num_points, float radius, color c, float detail = 0.5f );
		group add_group();

		template< typename T, typename... Args > T add( Args&&... a ) { T o( std::forward< Args >( a )... ); attach( o ); return o; }

		void attach( object& o );
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
