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

	mesh::mesh( const xo::path& filename ) :
	group()
	{
		osg::ref_ptr< osg::Node > file_node;
		if ( filename.extension() == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename.string() );
		node_->addChild( file_node );
	}

	mesh::mesh( const shape& s, const color& col, float detail ) :
	group()
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd;

		switch ( s.index() )
		{
		case shape_type::sphere:
			sd = new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), std::get<xo::sphere>(s).radius_ ), hints );
			break;
		case shape_type::box:
		{
			auto d = dim( s );
			sd = new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), d.x, d.y, d.z ), hints );
			break;
		}
		case shape_type::cylinder:
			sd = new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), std::get<xo::cylinder>( s ).radius_, std::get<xo::cylinder>( s ).height_ ), hints );
			break;
		case shape_type::capsule:
			sd = new osg::ShapeDrawable( new osg::Capsule( osg::Vec3( 0.0f, 0.0f, 0.0f ), std::get<xo::capsule>( s ).radius_, std::get<xo::capsule>( s ).height_ ), hints );
			break;
		case shape_type::cone:
			sd = new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), std::get<xo::cone>( s ).radius_, std::get<xo::cone>( s ).height_ ), hints );
			break;
		default: xo_error( "Cannot create mesh from shape" );
		}

		sd->setColor( to_osg( col ) );
		auto g = new osg::Geode;
		g->addDrawable( sd );
		node_->addChild( g );
	}

	mesh::~mesh()
	{
	}

	mesh& mesh::scale( const vec3f& s )
	{
		osg_trans_node().setScale( to_osg( s ) );
		return *this;
	}

	void mesh::set_color( const color& c )
	{
		dynamic_cast<osg::ShapeDrawable*>( node_->getChild( 0 )->asGeode()->getDrawable( 0 ) )->setColor( to_osg( c ) );
	}
}
