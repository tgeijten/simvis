#pragma once

#include "simvis_api.h"
#include "types.h"
#include "color.h"
#include <osg/PositionAttitudeTransform>
#include "xo/geometry/vec3_type.h"
#include "xo/geometry/quat_type.h"
#include "xo/filesystem/path.h"
#include "xo/shape/shape.h"

namespace vis
{
	class SIMVIS_API node
	{
	public:
		node( node* parent );
		node( const node& other ) : node_( other.node_ ) {}
		virtual ~node();

		void attach( node& o );
		void detach( node& o );
		void detach_all();
		void release();

		size_t size() const;
		bool has_parent() const;

		void show( bool show );
		void set_material( material& m );

		void transform( const transformf& t );
		void pos( const vec3f& p );
		void ori( const quatf& q );
		void pos_ori( const vec3f& p, const quatf& q ) { pos( p ); ori( q ); }

		explicit operator bool() const { return node_ != nullptr; }
		osg::Node* osg_node() { return node_; }
		osg::Group& osg_group() { return *node_; }
		osg::PositionAttitudeTransform& osg_trans_node() { return static_cast<osg::PositionAttitudeTransform&>( *node_ ); }

	protected:
		osg::ref_ptr< osg::Group > node_;
	};
}
