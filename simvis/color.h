#pragma once

#include "prerequisites.h"
#include <cstdint>

namespace vis
{
	struct SIMVIS_API color
	{
		color() : value( std::uint32_t( 0 ) ) {}
		color( std::uint32_t v ) : value( v ) {}
		color( double r, double g, double b, double a = 1.0 ) { set( r, g, b, a ); }
		color( float r, float g, float b, float a = 1.0 ) { set( r, g, b, a ); }

		template< typename T > color& set( T r, T g, T b, T a )
		{ value = int( r * 255.5 ) << 24 | int( g * 255.5 ) << 16 | int( b * 255.5 ) << 8 | int( a * 255.5 ); return *this; }

		float r() const { return float( ( value >> 24 ) & 255 ) / 255; }
		float g() const { return float( ( value >> 16 ) & 255 ) / 255; }
		float b() const { return float( ( value >> 8 ) & 255 ) / 255; }
		float a() const { return float( value & 255 ) / 255; }

		std::uint32_t value;
	};

	template< typename T > inline color operator*( T s, const color& c ) { return color( s * c.r(), s * c.g(), s * c.b(), s * c.a() ); }
	template< typename T > inline color operator*( const color& c, T s ) { return color( s * c.r(), s * c.g(), s * c.b(), s * c.a() ); }

	inline color operator+( const color& c1, const color& c2 ) { return color( c1.r() + c2.r(), c1.g() + c2.g(), c1.b() + c2.b(), c1.a() + c2.a() ); }
	inline color operator-( const color& c1, const color& c2 ) { return color( c1.r() - c2.r(), c1.g() - c2.g(), c1.b() - c2.b(), c1.a() - c2.a() ); }

	inline color mix_color( const color& col1, const color& col2, double w1 ) { return w1 * col1 + ( 1.0f - w1 ) * col2; }

	inline color make_red( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br*(1-sat) ); }
	inline color make_yellow( double br = 1.0, double sat = 1.0 ) { return color( br, br, br*(1-sat) ); }
	inline color make_green( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br*(1-sat) ); }
	inline color make_cyan( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br ); }
	inline color make_blue( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br*(1-sat), br ); }
	inline color make_magenta( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br ); }
	inline color make_white( double br = 1.0 ) { return color( br, br, br ); }
}
