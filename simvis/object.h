#pragma once

#include "prerequisites.h"
#include "osg/Node"

namespace simvis
{
	class SIMVIS_API object 
	{
	public:
		object() {}
		virtual ~object() {}

		virtual void show( bool show );
		virtual void color( const flut::math::vec4f& c );

		virtual osg::Node* osg_node() = 0;
	};
}
