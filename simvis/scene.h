#pragma once

#include "mesh.h"
#include "arrow.h"
#include "path.h"
#include "object.h"

namespace simvis
{
	class SIMVIS_API scene : public object
	{
	public:
		scene() {}
		~scene() {}

		enum class display_flag { shadows, backlight, floor };

		mesh make_mesh( const string& filename );
		mesh make_sphere();
		mesh make_cube();
		mesh make_cylinder();
		arrow make_arrow();
		path make_path();

		void attach( object& o );
		void detach( object& o );

		virtual osg::Node* osg_node() override { return group; }

	private:
		osg::ref_ptr< osg::Group > group;
	};
}
