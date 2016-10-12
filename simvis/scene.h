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
		virtual ~scene();

		light add_light( const vec3f& pos, const color& c );
	};
}
