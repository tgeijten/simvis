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

		void show( bool show );
		void set_color( const color& col, float specular = 1.0f, float shinyness = 15.0f, float ambient = 0.0f, float emissive = 0.0f );

		virtual osg::Node* osg_node() = 0;
	};
}
