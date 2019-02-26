#pragma once

#include "object.h"
#include "osg/Group"
#include "mesh.h"
#include "group.h"

namespace vis
{
	class SIMVIS_API trail : public object
	{
	public:
		trail() {}
		trail( size_t num_points, float radius, color c, float detail = 0.5f );
		virtual ~trail() {}

		template< typename Iter >
		void set_points( Iter b, Iter e, float relative_width = 1.0f );

		virtual osg::Node* osg_node() override { return parent.osg_node(); }

	private:
		void resize( size_t num_points );

		color col;
		float detail;
		float radius;
		group parent;
		std::vector< mesh > points;
		std::vector< mesh > cylinders;
	};

	template< typename Iter >
	void vis::trail::set_points( Iter b, Iter e, float relative_width )
	{
		if ( e - b != points.size() ) resize( e - b );
		for ( size_t i = 0; i < points.size(); ++i ) points[ i ].pos( *( b + i ) );
		for ( size_t i = 0; i < cylinders.size(); ++i ) {
			auto delta = *( b + i + 1 ) - *( b + i );
			cylinders[ i ].pos_ori( *( b + i ) + 0.5f * delta, quat_from_directions( vec3f::unit_z(), vec3f( normalized( delta ) ) ) );
			cylinders[ i ].scale( vec3f( relative_width, relative_width, delta.length() ) );
		}
	}

}
