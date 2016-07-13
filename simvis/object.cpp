#include "object.h"
#include "osg/Group"
#include "osg/Material"
#include "osg_tools.h"

namespace vis
{
	
	void object::show( bool show )
	{

	}

	void object::set_color( const color& col, float specular /*= 1.0f*/, float shinyness /*= 15.0f*/, float ambient /*= 0.0f*/, float emissive /*= 0.0f */ )
	{
		osg::ref_ptr< osg::Material > mat = new osg::Material;
		mat->setDiffuse( osg::Material::FRONT, make_osg( col ) );
		mat->setSpecular( osg::Material::FRONT, osg::Vec4( specular, specular, specular, 1.0) );
		mat->setAmbient( osg::Material::FRONT, make_osg( col ) * ambient );
		mat->setEmission( osg::Material::FRONT, make_osg( col ) * emissive );
		mat->setShininess( osg::Material::FRONT, 25.0 );

		osg_node()->getOrCreateStateSet()->setAttribute( mat );
	}
}
