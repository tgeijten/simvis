#pragma once

#include "mesh.h"
#include "node.h"
#include "arrow.h"

namespace vis
{
	class SIMVIS_API axes : public node
	{
	public:
		axes() {}
		axes( node& parent, vec3f length, float detail ) : axes( parent, length, 0.005f, detail ) {}
		axes( node& parent, vec3f length, float radius, float detail );
		axes( const axes& ) = delete;
		axes& operator=( const axes& ) = delete;
		axes( axes&& ) = default;
		axes& operator=( axes&& ) = default;

		void show( bool s );
		
	private:
		mesh x_arrow;
		mesh y_arrow;
		mesh z_arrow;
	};
}
 