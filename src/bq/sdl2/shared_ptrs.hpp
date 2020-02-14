/*
 * shares.hpp
 *
 *  Created on: Feb 4, 2020
 *      Author: badquanta
 */

#ifndef SDL2_SHARED_PTRS_HPP_
#define SDL2_SHARED_PTRS_HPP_
#include <memory>
/** std::shared_ptrs used by library for GC. **/
namespace bq {
  namespace sdl2 {
    /** Wrapper class to SDL_Renderer **/
    class Renderer;
    /**
     * Refrence counted pointer to `Renderer` instance.
     */
    typedef std::shared_ptr<sdl2::Renderer> Renderer_sptr;
    /** Wrapper class to SDL_Surface **/
    class Surface;
    /**
     * Refrence counted pointer to `Surface` instance.
     */
    typedef std::shared_ptr<sdl2::Surface> Surface_sptr;
    /** Manager of SDL_Texture* **/
    class Texture;
    /**
     * Refrence counted pointer to `Texture` instance.
     */
    typedef std::shared_ptr<sdl2::Texture> Texture_sptr;
    /** Manager of SDL_Window* **/
    class Window;
    /**
     * Refrence counted pointer to `Window` instance.
     */
    typedef std::shared_ptr<sdl2::Window> Window_sptr;
    /** Manager of TTF_Font* (true type Fonts.) **/
    class TTF;
    /**
     * Refrence counted pointer to `TTF` instance (fonts).
     */
    typedef std::shared_ptr<sdl2::TTF> TTF_sptr;
    /** Manager of SDL_Joystick* **/
    class Joystick;
    /**
     * Refrence counted pointer to `Joystick` instance.
     */
    typedef std::shared_ptr<sdl2::Joystick> Joystick_sptr;
    /** Manager of SDL_Cursor* **/
    class MouseCursor;
    /**
     * Refrence counted pointer to `MouseCursor` instances.
     */
    typedef std::shared_ptr<sdl2::MouseCursor> MouseCursor_sptr;
    /** Manager of SDL_Haptic* **/
    class Haptic;
    /** Reference counted pointer to `Haptic` instance **/
    typedef std::shared_ptr<Haptic> Haptic_sptr;

    namespace audio {
      class Cvt;
      typedef std::shared_ptr<Cvt> Cvt_sptr;
      class Spec;
      typedef std::shared_ptr<Spec> Spec_sptr;
      class Stream;
      typedef std::shared_ptr<Stream> Stream_sptr;
    }

  }
}

#endif /* SDL2_SHARED_PTRS_HPP_ */
