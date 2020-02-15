find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(
	# Deps. 
	${BQ_UTILS_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS} 
	${SDL2_IMAGE_INCLUDE_DIRS} 
	${SDL2_TTF_INCLUDE_DIRS} 
	${SDL2_MIXER_INCLUDE_DIRS}
) 
add_library(bq_sdl2 SHARED ./audio.cpp audio/Cvt.cpp audio/Spec.cpp audio/Stream.cpp	
EventDispatch.cpp 
GameController.cpp	
Haptic.cpp 
image.cpp 
Joystick.cpp 
keyboard.hpp keyboard.cpp
Log.cpp
mix.cpp mix/Chunk.cpp mix/Music.cpp MouseCursor.cpp Renderer.cpp Subsystem.cpp Surface.cpp Texture.cpp Timer.cpp ttf/TTF.cpp Video.cpp Window.cpp)
add_dependencies(bq_sdl2 bq_utils)
target_link_libraries(bq_sdl2 ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${BQ_UTIL_LIBRARIES})

foreach(X 
	Sdl2 
	Window 
	Video 
	Timer 
	Texture 
	Surface 
	Subsystem 
	Renderer 
	MouseCursor 
	image 
	Haptic 
)
	message(STATUS "making ${X}_test")
	add_executable("${X}_test" "${X}_test.cpp")
	target_link_libraries("${X}_test" bq_sdl2)
	add_dependencies("${X}_test" doctest)
	target_include_directories("${X}_test" PUBLIC "${DOCTEST_INCLUDE_DIR}")
	add_test("${X}_test" "${X}_test")
endforeach()


