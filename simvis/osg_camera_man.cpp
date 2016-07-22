#include "osg_camera_man.h"

using namespace osg;

namespace vis
{
	osg_camera_man::osg_camera_man() :
		osgGA::OrbitManipulator(),
		orbit_yaw( 0 ),
		orbit_pitch( -5 )
	{
		setAllowThrow( false );
		_distance = 5;
		_center = Vec3d( 0, 1, 0 );

		updateRotation();

		osg::Vec3d eye, center, up;
		getTransformation( eye, center, up );
		setHomePosition( eye, center, up );
	}

	osg_camera_man::~osg_camera_man() {}

	bool osg_camera_man::performMovementLeftMouseButton( const double eventTimeDelta, const double dx, const double dy )
	{
		orbit_pitch += degree( pitch_scale * dy );
		orbit_yaw -= degree( yaw_scale * dx );

		updateRotation();

		return true;
	}

	void osg_camera_man::updateRotation()
	{
		auto yaw = osg::Quat( orbit_yaw.rad_value(), osg::Vec3d( 0, 1, 0 ) );
		auto pitch = osg::Quat( orbit_pitch.rad_value(), osg::Vec3d( 1, 0, 0 ) );
		_rotation = pitch * yaw;
	}

	bool osg_camera_man::performMovementMiddleMouseButton( const double eventTimeDelta, const double dx, const double dy )
	{
		zoomModel( dy * zoom_scale, false );

		return true;
	}

	bool osg_camera_man::performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy )
	{
		// pan model
		float scale = -pan_scale * _distance;
		panModel( dx * scale, dy * scale );

		return true;
	}
}
