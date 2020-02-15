# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_sdl2
	VERSION "0.0.0"
)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/scripts)
# Externals & Settings 
include("scripts/external_projects.cmake")
include("scripts/project_settings.cmake")
# Sub directories
add_subdirectory(src)
# Installation configuration
install(TARGETS bq_sdl2	 
#	LIBRARY bq_sdl2
	DESTINATION bq_sdl2
	PUBLIC_HEADER ${bq_sdl2_PUBLIC_INCLUDE_DIRECTORIES}
)



