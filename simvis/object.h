#pragma once

#include "prerequisites.h"
#include "color.h"
#include "osg/Node"

namespace vis
{
	class SIMVIS_API object 
	{
	public:
		object() {}
		virtual ~object() {}

		virtual void show( bool show );
		virtual void set_color( const color& c );

		virtual osg::Node* osg_node() = 0;
	};
}
