#pragma once

#include "group.h"
#include "xo/geometry/shape.h"

namespace vis
{
	class SIMVIS_API plane : public group
	{
	public:
		plane() : group() {}
		plane( float x_width, float z_width, const xo::path& image );
		plane( int x_tiles, int z_tiles, float tile_size, color a, color b );
	};
}
