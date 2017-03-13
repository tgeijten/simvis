#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "scene.h"
#include "osg/Material"
#include "flut/string_tools.hpp"

namespace vis
{
	mesh::mesh( group& parent, const string& filename ) :
	group()
	{
		osg::ref_ptr< osg::Node > file_node;
		if ( flut::get_filename_ext( filename ) == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename );

		node->addChild( file_node );
		parent.attach( *this );
	}

	mesh::mesh( group& parent, primitive_shape shape, const vec3f& dim, const color& col, float detail ) :
	group()
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd;

		switch ( shape )
		{
		case primitive_shape::sphere:
			sd = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), dim.length() ), hints );
			break;
		case primitive_shape::box:
			sd = new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), dim.x, dim.y, dim.z ), hints );
			break;
		case primitive_shape::cylinder:
			sd = new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), sqrt( dim.x * dim.x + dim.y * dim.y ), dim.z ), hints );
			break;
		case primitive_shape::capsule:
			sd = new osg::ShapeDrawable( new osg::Capsule( osg::Vec3( 0.0f, 0.0f, 0.0f ), sqrt( dim.x * dim.x + dim.y * dim.y ), dim.z ), hints );
			break;
		case primitive_shape::cone:
			sd = new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), sqrt( dim.x * dim.x + dim.y * dim.y ), dim.z ), hints );
			break;
		}

		sd->setColor( make_osg( col ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		node->addChild( g );

		//set_color( col );

		parent.attach( *this );
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

	mesh& mesh::show( bool b )
	{
		node->setNodeMask( b ? ~0 : 0 );
		return *this;
	}

	mesh& mesh::pos( const vec3f& pos )
	{
		osg_trans_node().setPosition( make_osg( pos ) );
		return *this;
	}

	mesh& mesh::ori( const quatf& ori )
	{
		osg_trans_node().setAttitude( make_osg( ori ) );
		return *this;
	}

	mesh& mesh::scale( const vec3f& s )
	{
		osg_trans_node().setScale( make_osg( s ) );
		return *this;
	}

	void mesh::set_color( const color& c )
	{
		dynamic_cast<osg::ShapeDrawable*>( node->getChild( 0 )->asGeode()->getDrawable( 0 ) )->setColor( make_osg( c ) );
	}

	mesh& mesh::transform( const transformf& t )
	{
		osg_trans_node().setPosition( make_osg( t.p ) );
		osg_trans_node().setAttitude( make_osg( t.q ) );
		return *this;
	}
}
