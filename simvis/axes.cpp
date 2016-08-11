#include "axes.h"

#include "arrow.h"

namespace vis
{
	axes::axes( group& s, float length, float detail )
	{
		s.attach( *this );
		x_arrow = add_arrow( 0.005f, make_red(), detail );
		y_arrow = add_arrow( 0.005f, make_green(), detail );
		z_arrow = add_arrow( 0.005f, make_blue(), detail );

		x_arrow.pos( vec3f::zero(), vec3f( length, 0, 0 ) );
		y_arrow.pos( vec3f::zero(), vec3f( 0, length, 0 ) );
		z_arrow.pos( vec3f::zero(), vec3f( 0, 0, length ) );
	}

	axes::~axes()
	{
	}
}
