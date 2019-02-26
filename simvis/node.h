#pragma once

#include "simvis_api.h"
#include "types.h"
#include "color.h"
#include <osg/PositionAttitudeTransform>
#include "xo/geometry/vec3_type.h"
#include "xo/geometry/quat_type.h"
#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

namespace vis
{
	class SIMVIS_API node
	{
	public:
		node();
		node( const node& other ) : node_( other.node_ ) {}
		node& operator=( const node& other ) { node_ = other.node_; return *this; }
		virtual ~node();

		mesh add_mesh( const xo::path& filename );
		mesh add_shape( const xo::shape& s, color c, float detail = 0.05f );
		arrow add_arrow( float radius, float head_radius, color c, float detail = 0.5f );
		axes add_axes( vec3f length, float detail = 0.5f );
		trail add_trail( size_t num_points, float radius, color c, float detail = 0.5f );
		//light add_light( const vec3f& pos, const color& c );
		node add_group();

		template< typename T, typename... Args > T add( Args&&... a ) { T o( std::forward< Args >( a )... ); attach( o ); return o; }

		void attach( node& o );
		void detach( node& o );
		void detach_all();
		void release();

		size_t size();

		void show( bool show );
		void set_material( material& m );
		material get_material();
		bool has_parent();

		virtual osg::Node* osg_node() { return node_; }
		osg::Group& osg_group() { return *node_; }

		osg::PositionAttitudeTransform& osg_trans_node() { return static_cast<osg::PositionAttitudeTransform&>( *node_ ); }

		virtual void transform( const transformf& t );
		virtual void pos( const vec3f& p );
		virtual void ori( const quatf& q );
		virtual void pos_ori( const vec3f& p, const quatf& q ) { pos( p ); ori( q ); }

	protected:
		osg::ref_ptr< osg::Group > node_;
	};
}
