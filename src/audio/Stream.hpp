/*
 * Stream.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_AUDIO_STREAM_HPP_
#define SDL2_AUDIO_STREAM_HPP_

namespace bq {
  namespace sdl2 {
    namespace audio {
      
      class Stream {
        public:
          Stream();
          virtual ~Stream();
          Stream(const Stream &other);
          Stream(Stream &&other);
          Stream& operator=(const Stream &other);
          Stream& operator=(Stream &&other);
      };
    
    } /* namespace audio */
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_AUDIO_STREAM_HPP_ */
