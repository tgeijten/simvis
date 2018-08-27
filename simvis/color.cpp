#include "color.h"
#include <array>

namespace vis
{
	vis::color make_from_hsv( float H, float S, float V )
	{
		H = fmod( H, 360.0f ) / 60.0f;
		float fract = H - floor( H );
		float P = V * ( 1.0f - S );
		float Q = V * ( 1.0f - S * fract );
		float T = V * ( 1.0f - S * ( 1.0f - fract ) );

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

	SIMVIS_API color make_unique_color( index_t idx )
	{
		static std::array< float, 10 > standard_hue{ 0, 60, 120, 180, 240, 300, 30, 210, 270, 330 };
		static std::array< float, 10 > standard_val{ 1, 0.75, 0.75, 0.75, 1, 1, 1, 0.75, 1, 1 };
		float hue = standard_hue[ idx % standard_hue.size() ];
		float sat = 1.0f / ( 1.0f + idx / standard_hue.size() );
		float val = standard_val[ idx % standard_hue.size() ];
		return make_from_hsv( hue, sat, val );
	}
}
