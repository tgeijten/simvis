#pragma once

#include "object.h"
#include "mesh.h"
#include "group.h"
#include "arrow.h"

namespace vis
{
	class SIMVIS_API axes : public group
	{
	public:
		axes( group& s, vec3f length, float detail );
		virtual ~axes();
		
	private:
		arrow x_arrow;
		arrow y_arrow;
		arrow z_arrow;
	};
}
