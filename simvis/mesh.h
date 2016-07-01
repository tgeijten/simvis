#pragma once

#include "object.h"
#include "osg/Geode"
#include "osg/PositionAttitudeTransform"

namespace simvis
{
	enum class primitive_shape { sphere, box, cylinder_x, cylinder_y, cylinder_z };

	class SIMVIS_API mesh : public object
	{
	public:
		mesh( primitive_shape shape, const vec3f& dim, const vec4f& color, float detail = 1.0f );
		mesh( const string& filename );
		virtual ~mesh() {}

		void pos( const vec3f& pos );
		void ori( const quatf& ori );
		void pos_ori( const vec3f& p, const quatf& o ) { pos( p ); ori( o ); }
		
		virtual osg::Node* osg_node() override { return node; }

	private:
		osg::ref_ptr< osg::PositionAttitudeTransform > node;
	};
}
