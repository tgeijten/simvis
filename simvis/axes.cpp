#include "stdafx.h"
#include "axes.h"

namespace vis
{
	
	axes::axes( group& s, float length )
	{
		axes_mesh = mesh( s, "resources/osg/axes.osgt" );
		axes_mesh.scale( vec3f( length, length, length ) );
	}

	axes::~axes()
	{

	}
}
