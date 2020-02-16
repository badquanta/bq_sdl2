/*
 * mix.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_MIX_HPP_
#define SDL2_MIX_HPP_
#include <SDL2/SDL_mixer.h>
namespace bq {
  namespace sdl2 {
    namespace mix {
      bool init(int flags=MIX_INIT_MP3);
      bool wasInit(int flags=0);
      void quit();
      bool open(int freq=MIX_DEFAULT_FREQUENCY,Uint16 form=MIX_DEFAULT_FORMAT,int chan=2,int chunksize =2048);
    }
  }
}



#endif /* SDL2_MIX_HPP_ */
