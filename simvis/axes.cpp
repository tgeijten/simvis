#include "axes.h"

#include "arrow.h"

namespace vis
{
	
	axes::axes( group& s, float length, float detail )
	{
		s.attach( parent );
		parent.add_arrow( 0.005f, make_red(), detail ).pos( vec3f::make_zero(), vec3f( length, 0, 0 ) );
		parent.add_arrow( 0.005f, make_green(), detail ).pos( vec3f::make_zero(), vec3f( 0, length, 0 ) );
		parent.add_arrow( 0.005f, make_blue(), detail ).pos( vec3f::make_zero(), vec3f( 0, 0, length ) );
	}

	axes::~axes()
	{
	}
}
