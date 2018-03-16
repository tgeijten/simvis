#pragma once

#if defined(_MSC_VER)
#	ifdef SIMVIS_EXPORTS
#		define SIMVIS_API __declspec(dllexport)
#	else
#		define SIMVIS_API __declspec(dllimport)
#	endif
#else
#	define SIMVIS_API
#endif

#include "xo/geometry/vec3_type.h"
#include "xo/geometry/vec4_type.h"
#include "xo/geometry/quat_type.h"
#include "xo/geometry/transform.h"
#include <string>

namespace vis
{
	class axes;
	class group;
	class scene;
	class mesh;
	class arrow;
	class trail;
	class arrow;
	class light;

	using std::string;

	using xo::vec3f;
	using xo::vec4f;
	using xo::quatf;
	using xo::transformf;
	using xo::degreef;
	using xo::radianf;
	using xo::path;
}
