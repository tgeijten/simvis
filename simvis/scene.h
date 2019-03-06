#pragma once

#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "color.h"
#include "light.h"
#include "node.h"

namespace vis
{
	class SIMVIS_API scene : public node
	{
	public:
		scene( bool use_shadows );
		scene( const scene& other ) = delete;

		light add_light( const vec3f& pos, const color& c );
	};
}
