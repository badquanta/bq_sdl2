##################
# all library TRINITYs
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
