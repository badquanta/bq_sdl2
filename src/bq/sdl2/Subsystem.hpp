/*
 * Subsystem.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_SUBSYSTEM_HPP_
#define SDL2_SUBSYSTEM_HPP_
#include <SDL2/SDL.h>
namespace bq {
  namespace sdl2 {
    bool init(Uint32 wanted = SDL_INIT_VIDEO);
    bool wasInit(Uint32 systems = 0);
    bool pollEvent(SDL_Event*);
    void quit();

    class Subsystem {
      public:
        Subsystem();
        virtual ~Subsystem();
        Subsystem(const Subsystem &other);
        Subsystem(Subsystem &&other);
        Subsystem& operator=(const Subsystem &other);
        Subsystem& operator=(Subsystem &&other);
    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_SUBSYSTEM_HPP_ */
