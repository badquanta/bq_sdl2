/*
 * Timer.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Timer.hpp"

namespace bq {
  namespace sdl2 {
    Uint32 getTicks(){
      return SDL_GetTicks();
    }
    void delay(Uint32 t){
      SDL_Delay(t);
    }
    Timer::Timer() {
      stop();
    }

    void Timer::start(bool restart){
      if((!isStarted())||restart){
      fStartedAt = getTicks();
      fPausedAt = 0;
      }
    }
    bool Timer::isStarted(){
      return (fStartedAt!=0);
    }

    void Timer::stop(){
      fStartedAt = 0;
      fPausedAt = 0;
    }

    void Timer::pause(){
      if(!isPaused()){
        fPausedAt = getTicks()-fStartedAt;
      }
    }

    bool Timer::isPaused(){
      return (isStarted()&&(fPausedAt!=0));
    }

    ticks Timer::resume(){
      if(isPaused()){
        ticks pauseElapse = fPausedAt;
        fStartedAt=getTicks()-fPausedAt;
        fPausedAt = 0;
        return pauseElapse;
      } else {
        return 0;
      }
    }

    ticks Timer::getElapsed(){
      if(!isStarted()){
        return 0;
      } else if(isPaused()){
        return fPausedAt;
      } else {
        return getTicks()-fStartedAt;
      }
    }

    Timer::~Timer() {
      // TODO Auto-generated destructor stub
    }
/**
    Timer::Timer(const Timer &other) {
      // TODO Auto-generated constructor stub

    }

    Timer::Timer(Timer &&other) {
      // TODO Auto-generated constructor stub

    }

    Timer& Timer::operator=(const Timer &other) {// @suppress("No return")
      // TODO Auto-generated method stub

    }

    Timer& Timer::operator=(Timer &&other) {// @suppress("No return")
      // TODO Auto-generated method stub

    }
**/
  } /* namespace sdl2 */
} /* namespace bq */
