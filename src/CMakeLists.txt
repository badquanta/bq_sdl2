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
# Macro to avoid repetative commands for each "component"
macro(component compName)
	target_sources(bq_sdl2 PRIVATE "${compName}.cpp")
	target_sources(bq_sdl2 PUBLIC "${compName}.hpp")
	set_target_properties(bq_sdl2 PROPERTIES PUBLIC_HEADER "${compName}.hpp")
	add_executable("${compName}_test" "${compName}_test.cpp" )
	# add the dependencies all tests for this project need:
	add_dependencies("${compName}_test" doctest)
	# link against libraries:		
	target_link_libraries("${compName}_test" bq_sdl2)
	add_dependencies("${compName}_test" doctest)	
	#target_link_libraries("${X}_test" PUBLIC bqpd)	
	#target_link_libraries("${X}_test" PRIVATE doctest::doctest)
	target_include_directories("${compName}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}" "${CMAKE_BINARY_DIR}/include")
	
	add_test("${compName}_test" "${compName}_test")
endmacro()
##################
# all library components
component(audio)
add_subdirectory(audio)#	audio/Cvt	audio/Spec audio/Stream
component(EventDispatch)
component(GameController)
component(Haptic)
component(image)
component(Joystick)
component(keyboard)
component(Log)
component(mix)
add_subdirectory(mix) #/Chunk mix/Music
component(MouseCursor)
component(Renderer)
component(Subsystem)
component(Surface)
component(Texture)
component(Timer)
#component(ttf)
add_subdirectory(ttf)	#ttf/TTF
component(Window)
component(sdl2)
