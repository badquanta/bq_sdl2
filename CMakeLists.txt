# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_sdl2
	VERSION "0.0.1"
	DESCRIPTION "A simple Object-Oriented SDL2 wrapper."
	LANGUAGES CXX
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/scripts/sdl2")
# Externals & Settings 
include("scripts/external_projects.cmake")
# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  message("SETTING UP ${PROJECT_NAME}")
  # * [ ] TODO: review CXX_STANDARD 17
  set(CMAKE_CXX_STANDARD 17)
  message("CMAKE_CXX_STANDARD IS ${CMAKE_CXX_STANDARD}")
    set(default_build_type "Release")
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
      message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
      set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
          STRING "Choose the type of build." FORCE)
      # Set the possible values of build type for cmake-gui
      set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif()
    message(STATUS "CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")
    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    enable_testing( )
    # Testing only available if this is the main app
    include(CTest)
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
    # Docs only available if this is the main app
    find_package(Doxygen)
    #
    if(Doxygen_FOUND)
    # (this will be run from the main project directory, so ./doc, not ./scripts/doc)
		add_subdirectory(docs)
		#
    else()
    #
		message(STATUS "Doxygen not found, not building docs")
		#
    endif()
    #
endif()
# Sub directories
add_subdirectory(src)
