#pragma once

#include "simvis_api.h"
#include "mesh.h"
#include "node.h"

namespace vis
{
	class SIMVIS_API arrow : public node
	{
	public:
		arrow() : node( nullptr ) {}
		arrow( const arrow& other ) : node( other ), cylinder( other.cylinder ), end_cone( other.end_cone ) {}
		arrow( node& parent, float radius, float head_radius, const color& c, float detail = 0.5f );
		virtual ~arrow();

		void pos( const vec3f& begin_pos, const vec3f& end_pos );

	private:
		mesh cylinder;
		mesh end_cone;
	};
}
