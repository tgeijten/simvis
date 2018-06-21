#pragma once

#include "group.h"
#include "xo/geometry/shape.h"

namespace vis
{
	class SIMVIS_API plane : public group
	{
	public:
		plane() : group() {}
		plane( const vec3f& width, const vec3f& height, const xo::path& image, float wrep = 1.0f, float hrep = 1.0f );
		plane( int x_tiles, int z_tiles, float tile_size, color a, color b );
	};
}
