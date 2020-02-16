/*
 * Subsystem_test.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Subsystem.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
namespace bq {
  namespace sdl2 {
    TEST_CASE("init & wasInit"){
      CHECK_FALSE(wasInit());
      CHECK(init());
      CHECK(wasInit());
      quit();
      CHECK_FALSE(wasInit());
    }

    TEST_CASE("init video makes events turn on..."){
      CHECK(init(SDL_INIT_VIDEO));
      CHECK(wasInit(SDL_INIT_EVENTS));
      CHECK_FALSE(wasInit(SDL_INIT_JOYSTICK));
      quit();
    }
  } /* namespace sdl2 */
} /* namespace bqpd */
