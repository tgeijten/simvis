#pragma once

#include "object.h"
#include "group.h"

namespace vis
{
	enum class primitive_shape { sphere, box, cylinder, capsule, cone };

	class SIMVIS_API mesh : public group
	{
	public:
		mesh() : group() {}
		mesh( const mesh& other ) : group( other ) {}
		mesh( group& parent, const string& filename );
		mesh( group& parent, primitive_shape shape, const vec3f& dim, const color& col, float detail = 1.0f );
		virtual ~mesh();

		mesh& show( bool b );
		mesh& pos( const vec3f& pos );
		mesh& ori( const quatf& ori );
		mesh& pos_ori( const vec3f& p, const quatf& o ) { pos( p ); ori( o ); return *this; }
		mesh& scale( const vec3f& s );
		
		virtual osg::Node* osg_node() override { return node; }
		virtual mesh& transform( const transformf& t ) override;
	};
}
