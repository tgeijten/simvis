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
		mesh( node& parent, const xo::path& filename );
		mesh( node& parent, const xo::shape& shape, const color& col, float detail = default_detail );

		mesh( const mesh& ) = delete;
		mesh& operator=( const mesh& ) = delete;
		mesh( mesh&& ) = default;
		mesh& operator=( mesh&& ) = default;

		mesh& scale( const vec3f& s );
		void set_color( const color& c );
	};
}
