/*
 * Window_test.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */

#include "Window.hpp"
#include "Subsystem.hpp"
#include "../util/bqdoctest.hpp"
namespace bq {

  namespace sdl2 {

    TEST_CASE("create(std::string_view) inits")
    {
      CHECK_EQ(Window::getCount(),0)
      ;
      Window_sptr win = Window::create("Doctest Window create");
      CHECK(wasInit(SDL_INIT_VIDEO))
      ;
      CHECK_EQ(Window::getCount(),1)
      ;
      win = nullptr;
      CHECK_EQ(Window::getCount(),0)
      ;
      quit();

      SUBCASE("position...") {
        SDL_Point where { 0, 0 };
        Window_sptr win = Window::create("#getPosition", 200,
            200);
        CHECK_NE(win, nullptr)
        ;
        CHECK_EQ(where.x, 0)
        ;
        where = win->getPosition();
        CHECK_NE(where.x, 0)
        ;
        int x = 0;
        int y = 0;
        CHECK_NE(where.x,x)
        ;
        CHECK_NE(where.y,y)
        ;
        win->getPosition(x, y);
        CHECK_EQ(where.x,x)
        ;
        CHECK_EQ(where.y,y)
        ;
        x += 100;
        y -= 100;
        win->setPosition(x, y);
        CHECK_NE(where.x,x)
        ;
        CHECK_NE(where.y,y)
        ;
        where = win->getPosition();
        CHECK_EQ(where.x,x)
        ;
      CHECK_EQ(where.y,y);

    }
    win = nullptr;
    quit();
  }

} /* namespace bqpd */
} /* namespace bqpd */
