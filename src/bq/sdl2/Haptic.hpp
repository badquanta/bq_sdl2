/*
 * Haptic.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_HAPTIC_HPP_
#define SDL2_HAPTIC_HPP_
#include <SDL2/SDL.h>
#include <bq/WeakPtrCache.hpp>
#include "Subsystem.hpp"
#include "shared_ptrs.hpp"
#include <mutex>
#include <map>
namespace bq {
  namespace sdl2 {
    namespace haptic {
      bool init();
      bool wasInit();
      Haptic_sptr open(int idx);
      Haptic_sptr open(const Joystick_sptr&);

    }

    class Haptic {
      public:
        static WeakPtrCache<SDL_Haptic*, Haptic, SDL_Haptic*> get_sptr;
        SDL_Haptic*sdl_haptic;
        Haptic(SDL_Haptic*);
        virtual ~Haptic();
        Haptic(const Haptic &other) = delete;
        Haptic(Haptic &&other) = delete;
        Haptic& operator=(const Haptic &other) = delete;
        Haptic& operator=(Haptic &&other) = delete;
    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_HAPTIC_HPP_ */
