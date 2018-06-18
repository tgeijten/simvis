#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "scene.h"
#include "osg/Material"
#include "xo/string/string_tools.h"

namespace vis
{
	using xo::shape;
	using xo::shape_type;

	mesh::mesh( const path& filename ) :
	group()
	{
		osg::ref_ptr< osg::Node > file_node;
		if ( filename.extension() == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename.str() );
		node->addChild( file_node );
	}

	mesh::mesh( const shape& s, const color& col, float detail ) :
	group()
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd;

		switch ( s.type() )
		{
		case shape_type::sphere:
			sd = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius() ), hints );
			break;
		case shape_type::box:
			sd = new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.x(), s.y(), s.z() ), hints );
			break;
		case shape_type::cylinder:
			sd = new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius(), s.height() ), hints );
			break;
		case shape_type::capsule:
			sd = new osg::ShapeDrawable( new osg::Capsule( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius(), s.height() ), hints );
			break;
		case shape_type::cone:
			sd = new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius(), s.height() ), hints );
			break;
		default: xo_error( "Cannot create mesh from " + s.name() );
		}

		sd->setColor( make_osg( col ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		node->addChild( g );
	}

	mesh::~mesh()
	{
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
}
