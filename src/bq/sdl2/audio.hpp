/*
 * audio.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_AUDIO_HPP_
#define SDL2_AUDIO_HPP_
#include "shared_ptrs.hpp"
namespace bq {
  namespace sdl2 {
    namespace audio {
      bool init();
      bool wasInit();
      Spec_sptr loadWAV(std::string_view file);
    }
  }
}




#endif /* SDL2_AUDIO_HPP_ */
