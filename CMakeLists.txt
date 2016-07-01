file (GLOB SOURCE_FILES "simvis/*.h" "simvis/*.cpp")

source_group("simvis" FILES ${SOURCE_FILES})

add_library(simvis SHARED ${SOURCE_FILES} ${SOURCE_FILES_OGRE})

# FLUT
set(FLUT_DIR "" CACHE PATH "Path to flut installation")
find_path(FLUT_INCLUDE_DIR NAMES "flut/types.hpp" PATHS "${FLUT_DIR}")
find_library(FLUT_LIB_DEBUG NAMES flut PATHS "${FLUT_DIR}/bin/${CONFIG_NAME}/Debug" "${LIBRARY_OUTPUT_PATH}/Debug")
find_library(FLUT_LIB_RELEASE NAMES flut PATHS "${FLUT_DIR}/bin/${CONFIG_NAME}/Release" "${LIBRARY_OUTPUT_PATH}/Release")
target_link_libraries(simvis debug ${FLUT_LIB_DEBUG} optimized ${FLUT_LIB_RELEASE})
include_directories( ${FLUT_INCLUDE_DIR} )

# target properties
set_target_properties(simvis PROPERTIES 
	DEFINE_SYMBOL simvis_EXPORTS 
	PROJECT_LABEL "simvis"
	OUTPUT_NAME simvis)
