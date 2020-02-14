/*
 * Timer.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_TIMER_HPP_
#define SDL2_TIMER_HPP_
#include <SDL2/SDL.h>
namespace bq {
  namespace sdl2 {
    typedef Uint32 ticks;
    ticks getTicks();
    void delay(Uint32);
    class Timer {
      public:
        Timer();
        virtual ~Timer();

        void start(bool restart=false);
        bool isStarted();
        void stop();
        void pause();
        bool isPaused();
        ticks resume();
        ticks getElapsed();

      private:

        ticks fStartedAt;
        ticks fPausedAt;

        Timer(const Timer &other)=delete;
        Timer(Timer &&other)=delete;
        Timer& operator=(const Timer &other)=delete;
        Timer& operator=(Timer &&other)=delete;
    };
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_TIMER_HPP_ */
