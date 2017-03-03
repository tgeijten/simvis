#include "axes.h"

#include "arrow.h"
#include "flut/math/quat.hpp"

namespace vis
{
	axes::axes( group& s, vec3f length, float radius, float head_radius, float detail )
	{
		s.attach( *this );
		x_arrow = add_capsule( radius, length.x, make_red(), detail );
		y_arrow = add_capsule( radius, length.y, make_green(), detail );
		z_arrow = add_capsule( radius, length.z, make_blue(), detail );

		x_arrow.pos_ori( vec3f( 0.5f * length.x, 0, 0 ), flut::math::quat_from_euler( degreef( 0 ), degreef( 90 ), degreef( 0 ) ) );
		y_arrow.pos_ori( vec3f( 0, 0.5f * length.y, 0 ), flut::math::quat_from_euler( degreef( 90 ), degreef( 0 ), degreef( 0 ) ) );
		z_arrow.pos( vec3f( 0, 0, 0.5f * length.z ) );
	}

	axes::~axes()
	{
	}
}
