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

namespace vis
{
	constexpr double default_detail = 0.8;
}
