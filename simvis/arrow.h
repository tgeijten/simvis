#pragma once

#include "prerequisites.h"
#include "object.h"
#include "mesh.h"
#include "group.h"

namespace vis
{
	class SIMVIS_API arrow : public object
	{
	public:
		arrow() {}
		arrow( const arrow& other ) : root( other.root ), cylinder( other.cylinder ), end_cone( other.end_cone ) {}
		arrow( group& parent, float radius, const color& c, float detail );
		virtual ~arrow();

		void pos( const vec3f& begin_pos, const vec3f& end_pos );
		void arrow_head( float begin_size, float end_size );
		
		virtual osg::Node* osg_node() override { return root.osg_node(); }

	private:
		group root;
		mesh cylinder;
		mesh end_cone;
	};
}
