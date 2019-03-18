find_path( SIMVIS_INCLUDE_DIR NAMES "simvis/simvis_api.h" PATHS ${CMAKE_CURRENT_SOURCE_DIR} )

set(SOURCE_FILES
	"simvis/arrow.cpp"
	"simvis/arrow.h"
	"simvis/axes.cpp"
	"simvis/axes.h"
	"simvis/color.h"
	"simvis/color.cpp"
	"simvis/node.h"
	"simvis/node.cpp"
	"simvis/light.h"
	"simvis/light.cpp"
	"simvis/mesh.cpp"
	"simvis/mesh.h"
	"simvis/material.cpp"
	"simvis/material.h"
	"simvis/plane.cpp"
	"simvis/plane.h"
	"simvis/trail.cpp"
	"simvis/trail.h"
	"simvis/simvis_api.h"
	"simvis/types.h"
	"simvis/scene.cpp"
	"simvis/scene.h"
	"simvis/osg_tools.cpp"
	"simvis/osg_tools.h"
	"simvis/osg_camera_man.cpp"
	"simvis/osg_camera_man.h"
	"simvis/stdafx.h"
	)

# specify precompiled headers for MSVC
include( PrecompiledHeaders )
use_precompiled_headers( SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/simvis/stdafx.h" "simvis/stdafx.cpp" 256 )

source_group("simvis" FILES ${SOURCE_FILES})

add_library(simvis SHARED ${SOURCE_FILES})

# Require C++17 standard
set_target_properties(simvis PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(simvis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# OpenSceneGraph
set(OSG_DIR "" CACHE PATH "Installation directory of OpenSceneGraph")
FIND_PACKAGE( osg )
FIND_PACKAGE( osgwidget )
FIND_PACKAGE( osgqt )
FIND_PACKAGE( osgga )
FIND_PACKAGE( osgviewer )
FIND_PACKAGE( osgutil )
FIND_PACKAGE( osgdb )
FIND_PACKAGE( osgshadow )
FIND_PACKAGE( OpenThreads )

target_include_directories(simvis PRIVATE ${OSG_INCLUDE_DIR})

target_link_libraries(simvis
	xo
	${OSG_LIBRARIES}
	${OSGWIDGET_LIBRARIES}
	${OSGGA_LIBRARIES}
	${OSGVIEWER_LIBRARIES}
	${OSGQT_LIBRARIES}
	${OSGDB_LIBRARIES}
	${OSGSHADOW_LIBRARIES}
	${OPENTHREADS_LIBRARIES}
	)

# target properties
set_target_properties(simvis PROPERTIES 
	DEFINE_SYMBOL SIMVIS_EXPORTS 
	PROJECT_LABEL "simvis"
	OUTPUT_NAME simvis)
