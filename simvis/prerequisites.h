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

#include "flut/math/vec3_type.hpp"
#include "flut/math/vec4_type.hpp"
#include "flut/math/quat_type.hpp"
#include <string>

namespace vis
{
	class group;
	class scene;
	class mesh;
	class arrow;
	class path;
	class arrow;
	class light;

	using std::string;

	using flut::math::vec3f;
	using flut::math::vec4f;
	using flut::math::quatf;
}
