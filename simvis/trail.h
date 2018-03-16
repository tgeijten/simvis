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

		template< typename T >
		void set_points( const std::vector< xo::vec3_<T> >& pvec );

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

	template SIMVIS_API void trail::set_points( const std::vector< xo::vec3_< float > >& );
	template SIMVIS_API void trail::set_points( const std::vector< xo::vec3_< double > >& );
}
