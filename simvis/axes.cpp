#include "axes.h"

#include "arrow.h"

namespace vis
{
	axes::axes( group& s, vec3f length, float radius, float head_radius, float detail )
	{
		s.attach( *this );
		x_arrow = add_arrow( radius, head_radius, make_red(), detail );
		y_arrow = add_arrow( radius, head_radius, make_green(), detail );
		z_arrow = add_arrow( radius, head_radius, make_blue(), detail );

		x_arrow.pos( vec3f::zero(), vec3f( length.x, 0, 0 ) );
		y_arrow.pos( vec3f::zero(), vec3f( 0, length.y, 0 ) );
		z_arrow.pos( vec3f::zero(), vec3f( 0, 0, length.z ) );
	}

	axes::~axes()
	{
	}
}
