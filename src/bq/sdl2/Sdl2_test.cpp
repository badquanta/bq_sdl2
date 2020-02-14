/*
 * xDL_test.cpp
 *
 *  Created on: Jan 31, 2020
 *      Author: badquanta
 */


#include "Subsystem.hpp"
#include "Window.hpp"
#include "../util/bqdoctest.hpp"
namespace bq {
  namespace sdl2 {
    TEST_CASE("testing init")
    {
      CHECK(sdl2::init())
      ;
    }

    TEST_CASE("can create window")
    {
      Window_sptr win = Window::create(320, 200,
          "Test create window");
      CHECK((win != NULL))
      ;

    }
  }
} /* namespace bqpd */
