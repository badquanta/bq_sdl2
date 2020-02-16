/*
 * audio.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */
#include "audio.hpp"
#include "Subsystem.hpp"
namespace bq{
  namespace sdl2{
    namespace audio {
      bool init(){
         return wasInit() || sdl2::init(SDL_INIT_AUDIO);
       }
      bool wasInit(){
        return sdl2::wasInit(SDL_INIT_AUDIO);
      }
    }
  }
}
