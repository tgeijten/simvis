#pragma once

#include "object.h"
#include <osg/PositionAttitudeTransform>

namespace vis
{
	class SIMVIS_API group : public object
	{
	public:
		group();
		group( const group& other ) : node( other.node ) {}
		group& operator=( const group& other ) { node = other.node; return *this; }
		virtual ~group() {}

		mesh add_mesh( const path& filename );
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
		void detach( object& o );
		void detach_all();
		size_t size();

		osg::Group& osg_group() { return *node; }
		virtual osg::Node* osg_node() override { return node; }

		virtual group& transform( const transformf& t ) override;

	protected:
		osg::ref_ptr< osg::Group > node;
		osg::PositionAttitudeTransform& osg_trans_node() { return static_cast< osg::PositionAttitudeTransform& >( *node ); }
	};
}
