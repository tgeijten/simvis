#include "material.h"
#include "osg_tools.h"

namespace vis
{
	material::material( color diffuse, color specular, color ambient, color emissive, float shininess )
	{
		osg_mat = new osg::Material;
		osg_mat->setDiffuse( osg::Material::FRONT, make_osg( diffuse ) );
		osg_mat->setSpecular( osg::Material::FRONT, make_osg( specular ) );
		osg_mat->setAmbient( osg::Material::FRONT, make_osg( ambient ) );
		osg_mat->setEmission( osg::Material::FRONT, make_osg( emissive ) );
		osg_mat->setShininess( osg::Material::FRONT, shininess );
	}
}
