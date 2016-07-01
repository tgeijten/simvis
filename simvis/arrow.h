#pragma once

#include "object.h"
#include "osg/Group"

namespace simvis
{
	class SIMVIS_API arrow : public object
	{
	public:
		arrow( scene& s );
		virtual ~arrow();

		void pos( const vec3f& begin_pos, const vec3f& end_pos );
		void arrow_head( float begin_size, float end_size );
		
		virtual osg::Node* osg_node() override { return group; }

	private:
		osg::ref_ptr< osg::Group > group;
	};
}
