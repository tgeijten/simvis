#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "scene.h"
#include "osg/Material"
#include "flut/string_tools.hpp"

namespace vis
{
	mesh::mesh( group& s, const string& filename )
	{
		node = new osg::PositionAttitudeTransform;

		osg::ref_ptr< osg::Node > file_node;
		if ( flut::get_filename_ext( filename ) == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename );

		node->addChild( file_node );
		s.osg_group().addChild( node );
	}

	mesh::mesh( group& s, primitive_shape shape, const vec3f& dim, const color& col, float detail )
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
		node->addChild( g );

		//set_color( col );

		s.osg_group().addChild( node );
	}

	mesh::~mesh()
	{
		if ( node && node->referenceCount() == node->getNumParents() + 1 )
		{
			// this is the last ref, so remove all parents
			while ( node->getNumParents() > 0 )
				node->getParent( 0 )->removeChild( node );
		}
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

	void mesh::transform( const transformf& t )
	{
		node->setPosition( make_osg( t.p ) );
		node->setAttitude( make_osg( t.q ) );
	}

}
