#pragma once

#include "prerequisites.h"
#include "color.h"
#include "material.h"

namespace vis
{
	class SIMVIS_API object 
	{
	public:
		object() {}
		virtual ~object() {}

		void show( bool show );
		void set_material( material& m );
		material get_material();
		bool has_parent();

		virtual osg::Node* osg_node() = 0;
	};
}
