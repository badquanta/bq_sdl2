/*
 * keyboard.hpp
 *
 *  Created on: Feb 14, 2020
 *      Author: badquanta
 */

#ifndef SRC_BQ_SDL2_KEYBOARD_HPP_
#define SRC_BQ_SDL2_KEYBOARD_HPP_
#include <SDL2/SDL.h>
namespace bq {
  namespace sdl2 {
    namespace keyboard {
      const Uint8* getState(int*numkeys=nullptr);
    }
  }
}







#endif /* SRC_BQ_SDL2_KEYBOARD_HPP_ */
