#pragma once

#include "mesh.h"
#include "node.h"
#include "arrow.h"

namespace vis
{
	class SIMVIS_API axes : public node
	{
	public:
		axes() : node() {}
		axes( vec3f length, float detail ) : axes( length, 0.005f, detail ) {}
		axes( vec3f length, float radius, float detail );
		virtual ~axes();

		void show( bool s );
		
	private:
		mesh x_arrow;
		mesh y_arrow;
		mesh z_arrow;
	};
}
