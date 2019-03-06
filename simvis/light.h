#pragma once

#include "simvis_api.h"
#include <osg/LightSource>
#include "node.h"

namespace vis
{
	class SIMVIS_API light : public node
	{
	public:
		light() : node( nullptr ), light_source( nullptr ) {}
		explicit light( scene& parent, const vec3f& pos, const color& col );

		light( const light& ) = delete;
		light& operator=( const light& ) = delete;
		light( light&& ) = default;
		light& operator=( light&& ) = default;

		int get_number() { return light_source->getLight()->getLightNum(); }

		void pos( const vec3f& p );
		void attenuation( float c, float l, float q );

	private:
		osg::ref_ptr< osg::LightSource > light_source;
		static int unique_light_number;
	};
}
