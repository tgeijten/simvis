#pragma once

#include "color.h"
#include "osg/Material"

namespace vis
{
	class material
	{
	public:
		material() : osg_mat( nullptr ) {}
		material( color diffuse, color specular, color ambient, color emissive, float shininess );
		virtual ~material() {}

		void diffuse( color col );
		void specular( color col );
		void ambient( color col );
		void emissive( color col );
		void shininess( float s );

	private:
		osg::ref_ptr< osg::Material > osg_mat;
	};


}
