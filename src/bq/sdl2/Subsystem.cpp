/*
 * Subsystem.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Subsystem.hpp"

#include "image.hpp"
#include "mix.hpp"
#include "Log.hpp"
namespace bq {
  namespace sdl2 {
    bool init(Uint32 wanted) {
      Uint32 was_init = SDL_WasInit(wanted);
      if (was_init) {
        Log::System.verbose(__PRETTY_FUNCTION__);
        return (true);
      } else {
        if (SDL_Init(wanted) == 0) {
          Log::System.info("%s %d",__PRETTY_FUNCTION__,wanted);
          return (true);
        } else {
          Log::System.error("SDL Init Error: %s", SDL_GetError());
          return (false);
        }
      }
    }
    bool wasInit(Uint32 f){
      return SDL_WasInit(f)!=0;
    }
    void quit() {
      if (!SDL_QuitRequested()) {
        if (image::wasInit()) image::quit();
        if (mix::wasInit()) mix::quit();
        SDL_Quit();
      }
    }

    Subsystem::Subsystem() {
      // TODO Auto-generated constructor stub

    }

    Subsystem::~Subsystem() {
      // TODO Auto-generated destructor stub
    }

    Subsystem::Subsystem(const Subsystem &other) {
      // TODO Auto-generated constructor stub

    }

    Subsystem::Subsystem(Subsystem &&other) {// @suppress("No return")
      // TODO Auto-generated constructor stub

    }

    Subsystem& Subsystem::operator=(const Subsystem &other) {// @suppress("No return")
      // TODO Auto-generated method stub

    }

    Subsystem& Subsystem::operator=(Subsystem &&other) {// @suppress("No return")
      // TODO Auto-generated method stub

    }

  } /* namespace sdl2 */
} /* namespace bq */
