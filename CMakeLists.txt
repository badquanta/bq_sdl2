# PROJECT/CMakeList.txt
# - started in bq_TEMPLATE++
cmake_minimum_required (VERSION 3.13) 
project(bq_sdl2
	VERSION "0.0.1"
	DESCRIPTION "A simple Object-Oriented SDL2 wrapper."
	HOMEPAGE_URL "https://github.com/BadQuanta/bq_sdl"
	LANGUAGES CXX
)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/scripts")
# Externals & Settings 
include("external_projects.cmake")
include("project_settings.cmake")
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
