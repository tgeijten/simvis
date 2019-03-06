#include "axes.h"

#include "arrow.h"
#include "xo/geometry/quat.h"

namespace vis
{
	axes::axes( node& parent, vec3f length, float radius, float detail ) :
	node( &parent )
	{
		x_arrow = mesh( *this, xo::capsule{ radius, length.x }, make_red(), detail );
		y_arrow = mesh( *this, xo::capsule{ radius, length.y }, make_green(), detail );
		z_arrow = mesh( *this, xo::capsule{ radius, length.z }, make_blue(), detail );

		x_arrow.pos_ori( vec3f( 0.5f * length.x, 0, 0 ), xo::quat_from_euler( degreef( 0 ), degreef( 90 ), degreef( 0 ) ) );
		y_arrow.pos_ori( vec3f( 0, 0.5f * length.y, 0 ), xo::quat_from_euler( degreef( 90 ), degreef( 0 ), degreef( 0 ) ) );
		z_arrow.pos( vec3f( 0, 0, 0.5f * length.z ) );

		parent.attach( *this );
	}

	void axes::show( bool s )
	{
		x_arrow.show( s );
		y_arrow.show( s );
		z_arrow.show( s );
	}
}
