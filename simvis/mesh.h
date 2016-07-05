#pragma once

#include "object.h"
#include "osg/Geode"
#include "osg/PositionAttitudeTransform"

namespace simvis
{
	enum class primitive_shape { sphere, box, cylinder, cone };

	class SIMVIS_API mesh : public object
	{
	public:
		mesh() : node( nullptr ) {}
		mesh( const mesh& other ) : node( other.node ) {}
		mesh( scene& s, primitive_shape shape, const vec3f& dim, const color& col, float detail = 1.0f );
		mesh( const string& filename );
		virtual ~mesh() {}

		void pos( const vec3f& pos );
		void ori( const quatf& ori );
		void pos_ori( const vec3f& p, const quatf& o ) { pos( p ); ori( o ); }
		void scale( const vec3f& s );
		
		virtual osg::Node* osg_node() override { return node; }

	private:
		osg::ref_ptr< osg::PositionAttitudeTransform > node;
	};
}
