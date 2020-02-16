/*
 * Spec.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_AUDIO_SPEC_HPP_
#define SDL2_AUDIO_SPEC_HPP_

namespace bq {
  namespace sdl2 {
    namespace audio {
      
      class Spec {
        public:
          Spec();
          virtual ~Spec();
          Spec(const Spec &other);
          Spec(Spec &&other);
          Spec& operator=(const Spec &other);
          Spec& operator=(Spec &&other);
      };
    
    } /* namespace audio */
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_AUDIO_SPEC_HPP_ */
