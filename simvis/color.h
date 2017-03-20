#pragma once

#include "prerequisites.h"
#include <cstdint>

namespace vis
{
	struct SIMVIS_API color
	{
		color() : r( 0.0f ), g( 0.0f ), b( 0.0f ), a( 1.0f ) {}
		color( float pr, float pg, float pb, float pa = 1.0f ) : r( pr ), g( pg ), b( pb ), a( pb ) {}
		color( double pr, double pg, double pb, double pa = 1.0 ) : r( pr ), g( pg ), b( pb ), a( pb ) {}

		float r, g, b, a;
	};

	template< typename T > inline color operator*( T s, const color& c ) { return color( s * c.r, s * c.g, s * c.b, s * c.a ); }
	template< typename T > inline color operator*( const color& c, T s ) { return color( s * c.r, s * c.g, s * c.b, s * c.a ); }

	inline color operator+( const color& c1, const color& c2 ) { return color( c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a ); }
	inline color operator-( const color& c1, const color& c2 ) { return color( c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a ); }

	inline color make_mix( const color& col1, const color& col2, double w1 ) { return w1 * col1 + ( 1.0f - w1 ) * col2; }

	inline color make_red( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br*(1-sat) ); }
	inline color make_yellow( double br = 1.0, double sat = 1.0 ) { return color( br, br, br*(1-sat) ); }
	inline color make_green( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br*(1-sat) ); }
	inline color make_cyan( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br ); }
	inline color make_blue( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br*(1-sat), br ); }
	inline color make_magenta( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br ); }
	inline color make_white( double br = 1.0 ) { return color( br, br, br ); }

	inline color make_from_hsv( float H, float S, float V )
	{
		H = fmod( H, 360. ) / 60.;
		float fract = H - floor(H);
		float P = V * ( 1. - S );
		float Q = V *( 1. - S*fract );
		float T = V*( 1. - S*( 1. - fract ) );

		if ( 0. <= H && H < 1. )
			return color( V, T, P );
		else if ( 1. <= H && H < 2. )
			return color( Q, V, P );
		else if ( 2. <= H && H < 3. )
			return color( P, V, T );
		else if ( 3. <= H && H < 4. )
			return color( P, Q, V );
		else if ( 4. <= H && H < 5. )
			return color( T, P, V );
		else if ( 5. <= H && H < 6. )
			return color( V, P, Q );
		else
			return color( 0., 0., 0. );
	}
}
