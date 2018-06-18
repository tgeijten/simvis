#pragma once

#include "prerequisites.h"
#include "material.h"
#include "xo/geometry/transform.h"

namespace vis
{
	class SIMVIS_API object 
	{
	public:
		object() {}
		virtual ~object() {}

		void show( bool show );
		void set_material( material& m );
		material get_material();
		bool has_parent();

		virtual void transform( const transformf& t ) { XO_NOT_IMPLEMENTED; }
		virtual void pos( const vec3f& p ) { XO_NOT_IMPLEMENTED; }
		virtual void ori( const quatf& q ) { XO_NOT_IMPLEMENTED; }
		virtual void pos_ori( const vec3f& p, const quatf& q ) { pos( p ); ori( q ); }
		virtual osg::Node* osg_node() = 0;
	};
}
