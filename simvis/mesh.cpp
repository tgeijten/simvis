#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "scene.h"
#include "osg/Material"

namespace vis
{

	mesh::mesh( const string& filename )
	{
		node = new osg::PositionAttitudeTransform;
		auto mesh = osgDB::readNodeFile( filename );
		node->addChild( mesh );
	}

	mesh::mesh( scene& s, primitive_shape shape, const vec3f& dim, const color& col, float detail )
	{
		node = new osg::PositionAttitudeTransform;

		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd;

		switch ( shape )
		{
		case primitive_shape::sphere:
			sd = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), dim.length() ), hints );
			break;
		case primitive_shape::box:
			sd = new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), dim.x, dim.y, dim.z ) );
			break;
		case primitive_shape::cylinder:
			sd = new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), sqrt( dim.x * dim.x + dim.y * dim.y ), dim.z ) );
			break;
		case primitive_shape::cone:
			sd = new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), sqrt( dim.x * dim.x + dim.y * dim.y ), dim.z ) );
			break;
		}

		sd->setColor( make_osg( col ) );

		auto g = new osg::Geode;
		g->addDrawable( sd );

		osg::ref_ptr< osg::Material > mat = new osg::Material;
		mat->setDiffuse( osg::Material::FRONT, make_osg( col ) );
		mat->setSpecular( osg::Material::FRONT, osg::Vec4(0.5, 0.5, 0.5, 1.0) );
		mat->setAmbient( osg::Material::FRONT, osg::Vec4(0.1, 0.1, 0.1, 1.0) );
		mat->setEmission( osg::Material::FRONT, osg::Vec4(0.0, 0.0, 0.0, 1.0) );
		mat->setShininess( osg::Material::FRONT, 25.0 );

		g->getOrCreateStateSet()->setAttribute( mat );
		
		node->addChild( g );
		s.osg_root().addChild( node );
	}

	mesh::~mesh()
	{
		if ( node && node->referenceCount() == 2 )
			node->getParent( 0 )->removeChild( node );
	}

	void mesh::show( bool b )
	{
		node->setNodeMask( b ? ~0 : 0 );
	}

	void mesh::pos( const vec3f& pos )
	{
		node->setPosition( make_osg( pos ) );
	}

	void mesh::ori( const quatf& ori )
	{
		node->setAttitude( make_osg( ori ) );
	}

	void mesh::scale( const vec3f& s )
	{
		node->setScale( make_osg( s ) );
	}
}
