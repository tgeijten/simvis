#pragma once

#include "object.h"
#include "mesh.h"

namespace simvis
{
	class SIMVIS_API axes : public object
	{
	public:
		axes();
		virtual ~axes();
		
	private:
		mesh axes_mesh;
	};
}
