#pragma once

#include "prerequisites.h"
#include "osg/Vec3f"
#include "osg/Vec4f"
#include "osg/Quat"

namespace simvis
{
	inline osg::Vec3f make_osg( const vec3f& v ) { return osg::Vec3f( v.x, v.y, v.z ); }
	inline osg::Vec4f make_osg( const vec4f& v ) { return osg::Vec4f( v.x, v.y, v.z, v.w ); }
	inline osg::Quat make_osg( const quatf& v ) { return osg::Quat( v.x, v.y, v.z, v.w ); }
}
