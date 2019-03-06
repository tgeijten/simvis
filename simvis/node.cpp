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

	node::node( node* parent ) :
	node_( new osg::PositionAttitudeTransform )
	{
		if ( parent )
			parent->attach( *this );
	}

	//node::node( const node& other ) :
	//node_( new osg::PositionAttitudeTransform( other.osg_trans_node() ) )
	//{
	//	for ( unsigned int i = 0; i < other.osg_trans_node().getNumParents(); ++i )
	//		other.osg_trans_node().getParent( i )->addChild( node_ );
	//}

	//vis::node::node& node::operator=( const node& other )
	//{
	//	node_ = new osg::PositionAttitudeTransform( other.osg_trans_node() );
	//	for ( unsigned int i = 0; i < other.osg_trans_node().getNumParents(); ++i )
	//		other.osg_trans_node().getParent( i )->addChild( node_ );
	//}

	node::~node()
	{
		release();
	}

	void node::attach( node& o )
	{
		node_->addChild( o.node_ );
	}

	void node::detach( node& o )
	{
		node_->removeChild( o.node_ );
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

	size_t node::size() const
	{
		return node_->getNumChildren();
	}

	void node::show( bool show )
	{
		// this resets any node mask related setting
		// TODO: find a better way to show/hide nodes
		node_->setNodeMask( show ? ~0 : 0 );
	}

	void node::set_material( material& m )
	{
		node_->getOrCreateStateSet()->setAttribute( m.osg_mat() );
	}

	bool node::has_parent() const
	{
		return node_ && node_->getNumParents() > 0;
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
