#include "stdafx.h"

#include "trail.h"
#include "xo/geometry/vec3.h"
#include "xo/geometry/quat.h"

namespace vis
{
	trail::trail( node& parent, size_t num_points, float radius, color c, float detail ) :
	node( &parent ),
	radius( radius ),
	col( c ),
	detail( detail )
	{
		resize( num_points );
	}

	void trail::resize( size_t num_points )
	{
		size_t num_cylinders = num_points > 0 ? num_points - 1 : 0;

		// add points
		while ( points.size() < num_points )
			points.push_back( mesh( *this, xo::sphere{ radius * 1.02f }, col, detail ) );
		while ( cylinders.size() < num_cylinders )
			cylinders.push_back( mesh( *this, xo::cylinder{ radius, 1.0f }, col, detail ) );

		// remove points
		points.resize( num_points );
		cylinders.resize( num_cylinders );
	}
}
