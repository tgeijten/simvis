#pragma once

#include "object.h"
#include "osg/Group"

namespace simvis
{
	class SIMVIS_API path : public object
	{
	public:
		path() {}
		virtual ~path() {}

		void set_points( size_t count, vec3f points[] );

		virtual osg::Node* osg_node() override { return group; }

	private:
		osg::ref_ptr< osg::Group > group;
	};
}
