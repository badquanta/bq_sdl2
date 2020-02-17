#=======
# Each "NAME" gets translated into:
# "NAME.cpp", "NAME.hpp", "NAME_test.cpp"
# and each will be setup for the project by the TRINITY macro
# if there are sub-directories, simply `add_subdirectory(xyz)`
# and repeat the pattern.
TRINITY(audio)
add_subdirectory(audio)#	audio/Cvt	audio/Spec audio/Stream
TRINITY(EventDispatch)
TRINITY(GameController)
TRINITY(Haptic)
TRINITY(image)
TRINITY(Joystick)
TRINITY(keyboard)
TRINITY(Log)
TRINITY(mix)
add_subdirectory(mix) #/Chunk mix/Music
TRINITY(MouseCursor)
TRINITY(Renderer)
TRINITY(Subsystem)
TRINITY(Surface)
TRINITY(Texture)
TRINITY(Timer)
#TRINITY(ttf)
add_subdirectory(ttf)	#ttf/TTF
TRINITY(Window)
TRINITY(sdl2)

##################
