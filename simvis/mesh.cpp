#include "mesh.h"
#include "osg_tools.h"
#include "osgDB/ReadFile"
#include "osg/ShapeDrawable"
#include "scene.h"
#include "osg/Material"
#include "xo/string/string_tools.h"
#include <variant>

namespace vis
{
	using xo::shape;
	using xo::shape_type;

	mesh::mesh( node& parent, const xo::path& filename ) :
	node( &parent )
	{
		osg::ref_ptr< osg::Node > file_node;
		if ( filename.extension() == "vtp" )
			file_node = read_vtp( filename );
		else
			file_node = osgDB::readNodeFile( filename.string() );
		node_->addChild( file_node );
	}

	struct create_shape_visitor {
		create_shape_visitor( osg::TessellationHints* hints ) : hints_( hints ) {}

		osg::ShapeDrawable* operator()( const xo::sphere& s ) {
			return new osg::ShapeDrawable( new osg::Sphere( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::box& s ) {
			auto d = dim( s );
			return new osg::ShapeDrawable( new osg::Box( osg::Vec3( 0.0f, 0.0f, 0.0f ), d.x, d.y, d.z ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cylinder& s ) {
			return new osg::ShapeDrawable( new osg::Cylinder( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::capsule& s ) {
			return new osg::ShapeDrawable( new osg::Capsule( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::cone& s ) {
			return new osg::ShapeDrawable( new osg::Cone( osg::Vec3( 0.0f, 0.0f, 0.0f ), s.radius_, s.height_ ), hints_ );
		}

		osg::ShapeDrawable* operator()( const xo::plane& s ) {
			xo_error( "Cannot create mesh from shape" );
		}

		osg::TessellationHints* hints_;
	};

	mesh::mesh( node& parent, const shape& s, const color& col, float detail ) :
	node( &parent )
	{
		auto hints = new osg::TessellationHints;
		hints->setDetailRatio( detail );

		osg::ref_ptr< osg::ShapeDrawable > sd = std::visit( create_shape_visitor( hints ), s );
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
