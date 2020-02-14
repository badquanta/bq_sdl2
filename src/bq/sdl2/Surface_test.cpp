/*
 * Surface_test.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */

#include "Surface.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "Window.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../extern/onqtam/doctest.h"
namespace bq {
    TEST_CASE("window surface test 1"){
        sdl2::Window_sptr win = sdl2::Window::create(320,200,"Surface Test 1");
        sdl2::Surface_sptr surf = win->getSurface();
        CHECK((surf!=nullptr));
    }
} /* namespace bqpd */
