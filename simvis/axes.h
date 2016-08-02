#pragma once

#include "object.h"
#include "mesh.h"
#include "group.h"

namespace vis
{
	class SIMVIS_API axes : public object
	{
	public:
		axes( group& s, float length, float detail );
		virtual ~axes();
		
	private:
		group parent;
	};
}
