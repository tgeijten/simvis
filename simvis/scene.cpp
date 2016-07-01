#include "scene.h"

namespace simvis
{


	void scene::attach( object& o )
	{
		group->addChild( o.osg_node() );
	}

	void scene::detach( object& o )
	{
		group->removeChild( o.osg_node() );
	}

}
