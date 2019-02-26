#pragma once

#include "node.h"
#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

namespace vis
{
	class SIMVIS_API mesh : public node
	{
	public:
		mesh() : node( nullptr ) {}
		mesh( const mesh& other ) : node( other ) {}
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const xo::shape& shape, const color& col, float detail = default_detail );
		virtual ~mesh();

		mesh& scale( const vec3f& s );
		void set_color( const color& c );
	};
}
