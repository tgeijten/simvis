include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_path( SIMVIS_INCLUDE_DIR NAMES "simvis/prerequisites.h" PATHS ${CMAKE_CURRENT_SOURCE_DIR} )

set(SOURCE_FILES
	"simvis/arrow.cpp"
	"simvis/arrow.h"
	"simvis/axes.cpp"
	"simvis/axes.h"
	"simvis/color.h"
	"simvis/group.h"
	"simvis/group.cpp"
	"simvis/light.h"
	"simvis/light.cpp"
	"simvis/mesh.cpp"
	"simvis/mesh.h"
	"simvis/material.cpp"
	"simvis/material.h"
	"simvis/object.cpp"
	"simvis/object.h"
	"simvis/trail.cpp"
	"simvis/trail.h"
	"simvis/prerequisites.h"
	"simvis/scene.cpp"
	"simvis/scene.h"
	"simvis/osg_tools.cpp"
	"simvis/osg_tools.h"
	"simvis/osg_camera_man.cpp"
	"simvis/osg_camera_man.h"
	"simvis/stdafx.h"
	)

# specify precompiled headers for MSVC
if(MSVC)
	set(STD_AFX_SOURCE "simvis/stdafx.cpp")
	set(PCH_FILE "$(IntermediateOutputPath)stdafx.pch")
	set_source_files_properties( ${STD_AFX_SOURCE} PROPERTIES COMPILE_FLAGS "/Ycstdafx.h /Fp\"${PCH_FILE}\"" OBJECT_OUTPUTS "${PCH_FILE}" )
	set_source_files_properties( ${SOURCE_FILES} PROPERTIES COMPILE_FLAGS "/Yustdafx.h /FIstdafx.h /Fp\"${PCH_FILE}\"" OBJECT_DEPENDS "${PCH_FILE}" )
	list( APPEND SOURCE_FILES ${STD_AFX_SOURCE} )
endif(MSVC)

source_group("simvis" FILES ${SOURCE_FILES})

add_library(simvis SHARED ${SOURCE_FILES})

# FLUT
find_path(FLUT_INCLUDE_DIR NAMES "flut/system/types.hpp" PATHS "${FLUT_DIR}")
include_directories( ${FLUT_INCLUDE_DIR} )

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
INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIR})

target_link_libraries(simvis
	flut
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
