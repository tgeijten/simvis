#pragma once

#include "object.h"
#include "osg/Group"
#include "mesh.h"
#include "group.h"

namespace vis
{
	class SIMVIS_API path : public object
	{
	public:
		path() {}
		path( group& scene, size_t num_points, float radius, color c, float detail = 0.5f );
		virtual ~path() {}

		template< typename T >
		void set_points( const std::vector< flut::math::vec3_<T> >& pvec );

		virtual osg::Node* osg_node() override { return parent.osg_node(); }

	private:
		void add_remove_points( size_t num_points );

		color col;
		float detail;
		float radius;
		group parent;
		std::vector< mesh > points;
		std::vector< mesh > cylinders;
	};

	template SIMVIS_API void path::set_points( const std::vector< flut::math::vec3_< float > >& );
	template SIMVIS_API void path::set_points( const std::vector< flut::math::vec3_< double > >& );
}
