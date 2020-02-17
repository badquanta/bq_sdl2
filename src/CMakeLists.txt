# find_packages...
##################
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
##################
# all library components
list(APPEND BQ_SDL2_COMPONENTS
	audio	audio/Cvt	audio/Spec audio/Stream
	EventDispatch
	GameController
	Haptic
	image
	Joystick
	keyboard
	Log
	mix mix/Chunk mix/Music
	MouseCursor
	Renderer
	Subsystem
	Surface
	Texture
	Timer
	ttf/TTF
	Window
	sdl2
)
##################
# Convert the list of components into three lists of files:
foreach(X ${BQ_SDL2_COMPONENTS})
  list(APPEND BQ_SDL2_SOURCES "${X}.cpp")
  list(APPEND BQ_SDL2_HEADERS "${X}.hpp")
  list(APPEND BQ_SDL2_TESTS   "${X}_test.cpp")
  message("BQ_BQ_SDL2_COMPONENT+=${X}[.cpp|.hpp|_test.cpp]")
endforeach()
# Define this library as a target
add_library(bq_sdl2 SHARED ${BQ_SDL2_SOURCES})
# Add needed libraries.
target_link_libraries(bq_sdl2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BQ_UTIL_LIBRARIES})
# Public headers to install
set_target_properties(bq_sdl2 PROPERTIES PUBLIC_HEADER "${BQ_SDL2_HEADERS}")
# Describe install locations.
install(TARGETS bq_sdl2
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER	DESTINATION 	include/bq/sdl2
)
# Add needed include directories.
# Use the correct include directories; dpending on the interface?
<<<<<<< HEAD
target_include_directories(bq_sdl2 PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
$<INSTALL_INTERFACE:include/>
PRIVATE ${CMAKE_SOURCE_DIR}/src/
# More Include dirs...
${CMAKE_BINARY_DIR}/include
${BQ_UTILS_INCLUDE_DIRS}
${SDL2_INCLUDE_DIRS} 
${SDL2_IMAGE_INCLUDE_DIRS} 
${SDL2_TTF_INCLUDE_DIRS} 
${SDL2_MIXER_INCLUDE_DIRS}
)
# Needs this library:
add_dependencies(bq_sdl2 bq_utils)
# Generate associated testing.
if(BUILD_TESTING)

	# Generate associated testing.
	foreach(X ${BQ_SDL2_COMPONENTS})
		# output each test being declared.
		message(STATUS "ADDING ${X}_test")
		# add test executable
		add_executable("${X}_test" "${X}_test.cpp" )
		# add the dependencies all tests for this project need:
		add_dependencies("${X}_test" doctest)
		# link against libraries:		
		target_link_libraries("${X}_test" bq_sdl2)
		add_dependencies("${X}_test" doctest)	
		#target_link_libraries("${X}_test" PUBLIC bqpd)	
		#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
		target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}" "${CMAKE_BINARY_DIR}/include")
		add_test("${X}_test" "${X}_test")
	endforeach()
endif()
