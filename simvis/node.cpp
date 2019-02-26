#include "node.h"
#include "mesh.h"
#include "arrow.h"
#include "trail.h"
#include "material.h"
#include "osg_tools.h"
#include "axes.h"
#include "xo/shape/shape.h"
#include "light.h"

namespace vis
{
	using xo::shape;
	using xo::shape_type;

	node::node()
	{
		node_ = new osg::PositionAttitudeTransform;
	}

	node::~node()
	{
		release();
	}

	mesh node::add_mesh( const xo::path& filename )
	{
		mesh m( filename );
		attach( m );
		return m;
	}

	vis::mesh node::add_shape( const xo::shape& s, color c, float detail )
	{
		mesh m( s, c, detail );
		attach( m );
		return m;
	}

	arrow node::add_arrow( float radius, float head_radius, color c, float detail )
	{
		arrow m( radius, head_radius, c, detail );
		attach( m );
		return m;
	}

	axes node::add_axes( vec3f length, float detail )
	{
		axes a( length, detail );
		attach( a );
		return a;
	}

	trail node::add_trail( size_t num_points, float radius, color c, float detail )
	{
		trail t( num_points, radius, c, detail );
		attach( t );
		return t;
	}

	//light node::add_light( const vec3f& pos, const color& c )
	//{
	//	auto l = light( pos, c );
	//	attach( l );
	//	return l;
	//}

	node node::add_group()
	{
		node g;
		attach( g );
		return g;
	}

	void node::attach( node& o )
	{
		node_->addChild( o.osg_node() );
	}

	void node::detach( node& o )
	{
		node_->removeChild( o.osg_node() );
	}

	void node::detach_all()
	{
		node_->removeChildren( 0, node_->getNumChildren() );
	}

	void node::release()
	{
		if ( node_ && node_->referenceCount() == node_->getNumParents() + 1 )
		{
			// this is the last ref, so remove from all parents
			while ( node_->getNumParents() > 0 )
				node_->getParent( 0 )->removeChild( node_ );
		}
	}

	size_t node::size()
	{
		return node_->getNumChildren();
	}

	void node::show( bool show )
	{
		// this resets any node mask related setting
		// TODO: find a better way to show/hide nodes
		osg_node()->setNodeMask( show ? ~0 : 0 );
	}

	void node::set_material( material& m )
	{
		osg_node()->getOrCreateStateSet()->setAttribute( m.osg_mat() );
	}

	vis::material node::get_material()
	{
		// WARNING: untested
		auto* m = osg_node()->getOrCreateStateSet()->getAttribute( osg::StateAttribute::Type::MATERIAL );
		return material( dynamic_cast<osg::Material*>( m ) );
	}

	bool node::has_parent()
	{
		return osg_node()->getNumParents() > 0;
	}

	void node::transform( const transformf& t )
	{
		static_cast< osg::PositionAttitudeTransform& >( *node_ ).setPosition( to_osg( t.p ) );
		static_cast< osg::PositionAttitudeTransform& >( *node_ ).setAttitude( to_osg( t.q ) );
	}

	void node::pos( const vec3f& p )
	{
		static_cast<osg::PositionAttitudeTransform&>( *node_ ).setPosition( to_osg( p ) );
	}

	void node::ori( const quatf& q )
	{
		static_cast<osg::PositionAttitudeTransform&>( *node_ ).setAttitude( to_osg( q ) );
	}
}
