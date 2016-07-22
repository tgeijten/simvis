#include "stdafx.h"
#include "arrow.h"

#include "flut/math/quat.hpp"
#include "flut/math/vec3.hpp"
#include "flut/system/log.hpp"

namespace vis
{
	arrow::arrow( group& parent, float radius, const color& c, float detail )
	{
		parent.attach( root );
		cylinder = root.add_cylinder( radius, 1, c, detail );
		end_cone = root.add_cone( radius * 2, radius * 4, c, detail );
	}

	arrow::~arrow() {}

	void arrow::pos( const vec3f& begin_pos, const vec3f& end_pos )
	{
		vec3f dir = end_pos - begin_pos;
		auto q = flut::math::make_quat_from_directions( vec3f::make_unit_z(), dir );
		cylinder.pos_ori( begin_pos + 0.5f * dir, q );
		cylinder.scale( vec3f( 1, 1, dir.length() ) );
		end_cone.pos_ori( end_pos, q );
	}
}
