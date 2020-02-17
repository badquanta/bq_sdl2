# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_sdl2
	VERSION "0.0.1"
	DESCRIPTION "A simple Object-Oriented SDL2 wrapper."
	LANGUAGES CXX
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/scripts")
# Externals & Settings 
include("scripts/external_projects.cmake")
# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  
    set(default_build_type "Release")
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
      message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
      set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
          STRING "Choose the type of build." FORCE)
      # Set the possible values of build type for cmake-gui
      set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
	endif()
	message(STATUS "SETTING UP ${PROJECT_NAME} in configuration ${CMAKE_BUILD_TYPE}")
	# * [ ] TODO: review CXX_STANDARD 17
	set(CMAKE_CXX_STANDARD 17)
	message("CMAKE_CXX_STANDARD IS ${CMAKE_CXX_STANDARD}")    
    # TODO: Do we need this?
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	# Use testing...
    enable_testing( )
    # Testing only available if this is the main app
	include(CTest)
	# Set-up CPack
    set(PACK_GENERATOR "TGZ;DEB")
    set(CPACK_BINARY_DEB      ON) 
    set(CPACK_BINARY_TZ       OFF)
    set(CPACK_BINARY_STGZ     OFF)
	set(CPACK_STRIP_FILES     ON)
	set(CPACK_PACKAGE_NAME     ${PROJECT_NAME} )
	set(CPACK_PACKAGE_VERSION  ${VERSION})
	set(CPACK_PACKAGE_CONTACT  "Jon (BadQuanta) Sawyer")
	set(CPACK_PACKAGE_VENDOR   "U.F.P.")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A simple object oriented wrapper for SDL2")
	set(CPACK_PACKAGE_DESCRIPTION "A simple object oriented wrapper for SDL2 with std::shared_ptr garbage collection.")
	set(CPACK_RESOURCE_FILE_LICENSE     ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
	set(CPACK_RESOURCE_FILE_README      ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
	set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACKAGE_DESCRIPTION})
	set(CPACK_DEBIAN_PACKAGE_SECTION     "devel")
	set(CPACK_DEBIAN_PACKAGE_HOMEPAGE    "https://github.com/BadQuanta/bq_sdl")
	set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS   YES) #
	set(CPACK_DEBIAN_PACKAGE_DEPENDS    "libsdl2-dev, libsdl2-gfx-dev, libsdl2-image-dev, libsdl2-mixer-dev, libsdl2-net-dev, libsdl2-ttf-dev")
	set(CPACK_DEBIAN_PACKAGE_SUGGESTS    "")
	set(CPACK_DEBIAN_PACKAGE_CONFLICTS   "")
	set(CPACK_DEBIAN_PACKAGE_MAINTAINER  "Jon (BadQuanta) Sawyer <badquanta@gmail.com>")
    # Packaging only available if this is the main app
    include(CPack)   
endif()
# find_packages...
##################
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
#################
# bq_sdl2 library
# Define this library as a target
add_library(bq_sdl2 SHARED ${BQ_SDL2_SOURCES})
add_dependencies(bq_sdl2 bq_utils)
# Add needed libraries.
target_link_libraries(bq_sdl2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BQ_UTIL_LIBRARIES})
# Describe install locations.
install(TARGETS bq_sdl2
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/sdl2
)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/src/ DESTINATION include/bq/sdl2 FILES_MATCHING PATTERN "*.hpp")
# Add needed include directories.
# Use the correct include directories; dpending on the interface?
target_include_directories(bq_sdl2 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
		$<INSTALL_INTERFACE:include/>
	PRIVATE ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR}/include ${BQ_UTILS_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} 	${SDL2_IMAGE_INCLUDE_DIRS} 	${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS}
)
###############
# Macro to avoid repetative commands for each: "TRINITY"
# (aka: "Source, Header, and Test")
macro(TRINITY compName)
	# Handle each source by adding it to the target
	target_sources(bq_sdl2 PRIVATE "${compName}.cpp")
	# Handle each header by adding it to the target AND
	target_sources(bq_sdl2 PUBLIC "${compName}.hpp")
	# Adding it to the target_properties (TODO: This may not be needed anymore)
	set_target_properties(bq_sdl2 PROPERTIES PUBLIC_HEADER "${compName}.hpp")
	# Add a target for each component's unit test.
	add_executable("${compName}_test" "${compName}_test.cpp" )
	# unit tests require this header-only package to compile, add it as a dependency.
	add_dependencies("${compName}_test" doctest)	
	# link each component's unit test agains the library as a whole.
	target_link_libraries("${compName}_test" bq_sdl2)
	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	# Setup the include directories for the tests	
	target_include_directories("${compName}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}" "${CMAKE_BINARY_DIR}/include")	
	# Register each test with the test-running framework.
	add_test("${compName}_test" "${compName}_test")
	# Tell the user that we've configured ("Shat") this component.
	message(STATUS "SHaT ${compName}")
endmacro()
# Now add all that source code for this library...
add_subdirectory(src)
