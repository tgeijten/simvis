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
		//void set_color( const color& col, float specular = 1.0f, float shinyness = 15.0f, float ambient = 0.0f, float emissive = 0.0f );
		bool has_parent();

		virtual osg::Node* osg_node() = 0;
	};
}
