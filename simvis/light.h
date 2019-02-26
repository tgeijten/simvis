#pragma once

#include "simvis_api.h"
#include <osg/LightSource>
#include "node.h"

namespace vis
{
	class SIMVIS_API light : public node
	{
	public:
		light() : light_source( nullptr ) {}
		light( const light& other ) : light_source( other.light_source ) {}
		explicit light( scene& s, const vec3f& pos, const color& col );
		virtual ~light() {}

		int get_number() { return light_source->getLight()->getLightNum(); }

		virtual osg::Node* osg_node() override { return light_source; }
		virtual void pos( const vec3f& p ) override;
		void attenuation( float c, float l, float q );

	private:
		osg::ref_ptr< osg::LightSource > light_source;
		static int unique_light_number;
	};
}
