#pragma once

#include "object.h"
#include <osg/Group>

namespace vis
{
	class SIMVIS_API group : public object
	{
	public:
		group();
		group( const group& other ) : node( other.node ) {}
		group& operator=( const group& other ) { node = other.node; return *this; }
		virtual ~group() {}

		mesh add_mesh( const string& filename );
		mesh add_sphere( float radius, color c, float detail = 0.5f );
		mesh add_cube( vec3f dim, color c );
		mesh add_cylinder( float radius, float height, color c, float detail = 0.5f );
		mesh add_cone( float radius, float height, color c, float detail = 0.5f );
		arrow add_arrow( float radius, color c, float detail = 0.5f );
		path add_path( size_t num_points, float radius, color c, float detail = 0.5f );

		void attach( object& o );
		void detach( object& o );
		void detach_all();
		size_t size();

		osg::Group& osg_group() { return *node; }
		virtual osg::Node* osg_node() override { return node; }

		virtual void transform( const transformf& t ) override;

	protected:
		osg::ref_ptr< osg::Group > node;
	};
}
