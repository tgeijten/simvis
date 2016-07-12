#pragma once

#include "object.h"
#include "osg/Group"
#include "mesh.h"

namespace vis
{
	class SIMVIS_API path : public object
	{
	public:
		path() {}
		path( scene& scene, size_t num_points, float radius, color c, float detail = 0.5f );
		virtual ~path() {}

		void set_points( const std::vector< vec3f >& pvec );

		virtual osg::Node* osg_node() override { return points.front().osg_node(); }

	private:
		std::vector< mesh > points;
		std::vector< mesh > cylinders;
	};
}
