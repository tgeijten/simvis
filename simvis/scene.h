#pragma once

#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "object.h"
#include "color.h"
#include "light.h"
#include "group.h"

namespace vis
{
	class SIMVIS_API scene : public group
	{
	public:
		scene( bool use_shadows );
		void create_tile_floor( int width, int heigh, int tile_size, color a, color b );
		//void create_textured_floor( int x_width, int z_width, const xo::path& image );
		virtual ~scene();

		light add_light( const vec3f& pos, const color& c );
	};
}
