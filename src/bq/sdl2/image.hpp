/*
 * Image.h
 *
 *  Created on: Feb 2, 2020
 *      Author: badquanta
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "shared_ptrs.hpp"
#include "Subsystem.hpp"

namespace bq {
  namespace sdl2 {
    namespace image {
      Surface_sptr load(std::string_view filename);
      bool init(Uint32 wanted = ::IMG_INIT_JPG);
      bool wasInit(Uint32 systems = 0);
      bool quit();

    }
  }
} /* namespace bq::sdl2 */

#endif /* IMAGE_HPP_ */
