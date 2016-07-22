#include "stdafx.h"
#include "object.h"
#include "osg/Group"
#include "osg/Material"
#include "osg_tools.h"

namespace vis
{
	
	void object::show( bool show )
	{
		// this resets any nodemask related setting
		// TODO: find a better way to show/hide nodes
		osg_node()->setNodeMask( show ? ~0 : 0 );
	}

	void object::set_material( material& m )
	{
		osg_node()->getOrCreateStateSet()->setAttribute( m.osg_mat() );
	}

	vis::material object::get_material()
	{
		// WARNING: untested
		auto* m = osg_node()->getOrCreateStateSet()->getAttribute( osg::StateAttribute::Type::MATERIAL );
		return material( dynamic_cast< osg::Material* >( m ) );
	}

	bool object::has_parent()
	{
		return osg_node()->getNumParents() > 0;
	}
}
