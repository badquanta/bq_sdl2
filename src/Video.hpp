/*
 * Video.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_VIDEO_HPP_
#define SDL2_VIDEO_HPP_

namespace bq {
  namespace sdl2 {

    class Video {
      public:
        Video();
        virtual ~Video();
        Video(const Video &other);
        Video(Video &&other);
        Video& operator=(const Video &other);
        Video& operator=(Video &&other);

    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_VIDEO_HPP_ */
