#pragma once

#include "object.h"
#include "group.h"

namespace vis
{
	enum class primitive_shape { sphere, box, cylinder, cone };

	class SIMVIS_API mesh : public group
	{
	public:
		mesh() : group() {}
		mesh( const mesh& other ) : group( other ) {}
		mesh( group& parent, const string& filename );
		mesh( group& parent, primitive_shape shape, const vec3f& dim, const color& col, float detail = 1.0f );
		virtual ~mesh();

		void show( bool b );
		void pos( const vec3f& pos );
		void ori( const quatf& ori );
		void pos_ori( const vec3f& p, const quatf& o ) { pos( p ); ori( o ); }
		void scale( const vec3f& s );
		
		virtual osg::Node* osg_node() override { return node; }

		virtual void transform( const transformf& t ) override;
	};
}
