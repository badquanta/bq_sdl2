/*
 * Conversion.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_AUDIO_CVT_HPP_
#define SDL2_AUDIO_CVT_HPP_

namespace bq {
  namespace sdl2 {
    namespace audio {
      
      class Cvt {
        public:
          Cvt();
          virtual ~Cvt();
          Cvt(const Cvt &other);
          Cvt(Cvt &&other);
          Cvt& operator=(const Cvt &other);
          Cvt& operator=(Cvt &&other);
      };
    
    } /* namespace audio */
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_AUDIO_CVT_HPP_ */
