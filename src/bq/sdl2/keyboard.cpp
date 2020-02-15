/*
 * keyboard.cpp
 *
 *  Created on: Feb 14, 2020
 *      Author: badquanta
 */
#include "keyboard.hpp"
namespace bq{
  namespace sdl2 {
    namespace keyboard {
      const Uint8* getState(int*numkeys){
        return SDL_GetKeyboardState(numkeys);
      }
    }
  }
}
