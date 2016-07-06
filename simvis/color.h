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

	static color make_red( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br*(1-sat) ); }
	static color make_yellow( double br = 1.0, double sat = 1.0 ) { return color( br, br, br*(1-sat) ); }
	static color make_green( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br*(1-sat) ); }
	static color make_cyan( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br, br ); }
	static color make_blue( double br = 1.0, double sat = 1.0 ) { return color( br*(1-sat), br*(1-sat), br ); }
	static color make_magenta( double br = 1.0, double sat = 1.0 ) { return color( br, br*(1-sat), br ); }
	static color make_white( double br = 1.0 ) { return color( br, br, br ); }
}
