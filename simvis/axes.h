#pragma once

#include "object.h"
#include "mesh.h"

namespace vis
{
	class SIMVIS_API axes : public object
	{
	public:
		axes( scene& s, float length );
		virtual ~axes();
		
	private:
		mesh axes_mesh;
	};
}
