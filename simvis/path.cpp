#include "stdafx.h"
#include "path.h"
#include "scene.h"
#include <flut/math/vec3.hpp>
#include "flut/math/quat.hpp"

namespace vis
{
	path::path( group& scene, size_t num_points, float radius, color c, float detail ) :
	radius( radius ),
	col( c ),
	detail( detail )
	{
		scene.attach( parent );
		add_remove_points( num_points );
	}

	template< typename T >
	void path::set_points( const std::vector< flut::math::vec3_<T> >& pvec )
	{
		if ( pvec.size() != points.size() )
			add_remove_points( pvec.size() );

		for ( size_t i = 0; i < points.size(); ++i )
			points[ i ].pos( pvec[ i ] );

		for ( size_t i = 0; i < cylinders.size(); ++i )
		{
			auto delta = pvec[ i + 1 ] - pvec[ i ];
			cylinders[ i ].pos( pvec[ i ] + T(0.5) * delta );
			cylinders[ i ].ori( make_quat_from_directions( vec3f::make_unit_z(), vec3f( normalized( delta ) ) ) );
			cylinders[ i ].scale( vec3f( 1.0f, 1.0f, delta.length() ) );
		}
	}

	void path::add_remove_points( size_t num_points )
	{
		size_t num_cylinders = num_points > 0 ? num_points - 1 : 0;

		// add points
		while ( points.size() < num_points )
			points.push_back( parent.add_sphere( radius * 1.05f, col, detail ) );
		while ( cylinders.size() < num_cylinders )
			cylinders.push_back( parent.add_cylinder( radius, 1.0f, col, detail ) );

		// remove points
		points.resize( num_points );
		cylinders.resize( num_cylinders );
	}
}
