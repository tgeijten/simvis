#pragma once

#include "object.h"
#include "group.h"
#include "xo/filesystem/path.h"
#include "xo/geometry/shape.h"

namespace vis
{
	class SIMVIS_API mesh : public group
	{
	public:
		mesh() : group() {}
		mesh( const mesh& other ) : group( other ) {}
		mesh( const xo::path& filename );
		mesh( const xo::shape& shape, const color& col, float detail = 1.0f );
		virtual ~mesh();

		mesh& scale( const vec3f& s );
		void set_color( const color& c );
	};
}
