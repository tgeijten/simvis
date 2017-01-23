#include "arrow.h"

#include "flut/math/quat.hpp"
#include "flut/math/vec3.hpp"
#include "flut/system/log.hpp"

namespace vis
{
	arrow::arrow( group& parent, float radius, float head_radius, const color& c, float detail )
	{
		parent.attach( root );
		cylinder = root.add_cylinder( radius, 1, c, detail );

		if ( head_radius > 0.0f )
			end_cone = root.add_cone( head_radius, head_radius * 2, c, detail );
	}

	arrow::~arrow()
	{
	}

	void arrow::pos( const vec3f& begin_pos, const vec3f& end_pos )
	{
		vec3f dir = end_pos - begin_pos;
		auto q = flut::math::quat_from_directions( vec3f::unit_z(), dir );
		cylinder.pos_ori( begin_pos + 0.5f * dir, q );
		cylinder.scale( vec3f( 1, 1, dir.length() ) );

		if ( end_cone.size() )
			end_cone.pos_ori( end_pos, q );
	}
}
