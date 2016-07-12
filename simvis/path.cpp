#include "path.h"
#include "scene.h"
#include <flut/math/vec3.hpp>
#include "flut/math/quat.hpp"

namespace vis
{
	path::path( scene& scene, size_t num_points, float radius, color c, float detail ) 
	{
		for ( size_t i = 0; i < num_points; ++i )
			points.push_back( scene.make_sphere( radius, c, detail ) );

		for ( size_t i = 0; i < num_points - 1; ++i )
			cylinders.push_back( scene.make_cylinder( radius, 1.0f, c, detail ) );
	}

	void path::set_points( const std::vector< vec3f >& pvec )
	{
		if ( pvec.size() != points.size() )
			return;

		for ( size_t i = 0; i < points.size(); ++i )
			points[ i ].pos( pvec[ i ] );

		for ( size_t i = 0; i < cylinders.size(); ++i )
		{
			auto delta = pvec[ i + 1 ] - pvec[ i ];
			cylinders[ i ].pos( pvec[ i ] + 0.5f * delta );
			cylinders[ i ].ori( make_quat_from_directions( vec3f::make_unit_z(), normalized( delta ) ) );
			cylinders[ i ].scale( vec3f( 1.0f, 1.0f, delta.length() ) );
		}
	}
}
