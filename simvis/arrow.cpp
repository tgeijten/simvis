#include "arrow.h"
#include "scene.h"
#include "flut/math/quat.hpp"
#include "flut/math/vec3.hpp"

namespace simvis
{
	
	arrow::arrow( scene& s, float radius, const color& c, float detail )
	{
		cylinder = s.make_cylinder( radius, 0, c, detail );
		end_cone = s.make_cone( radius * 2, radius * 2, c, detail );
	}

	arrow::~arrow() {}

	void arrow::pos( const vec3f& begin_pos, const vec3f& end_pos )
	{
		vec3f dir = end_pos - begin_pos;
		auto q = flut::math::make_quat_from_directions( vec3f::make_unit_z(), dir );
		cylinder.pos_ori( begin_pos, q );
		cylinder.scale( vec3f( 1, 1, dir.length() ) );
		end_cone.pos_ori( end_pos, q );
	}
}
