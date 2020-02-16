/*
 * mix.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */


#include "mix.hpp"
#include "Log.hpp"
#include "Subsystem.hpp"
#include "audio.hpp"

namespace bq{
  namespace sdl2{
    namespace mix{
      static Log& log=Log::Audio;
      bool init(int flags){
        if(wasInit(flags)){
          log.verbose("Mixer ready.");
          return true;
        } else {
          if(audio::init() && (Mix_Init(flags)==flags)){
            log(__PRETTY_FUNCTION__);
            return true;
          } else {
            log.errorMIX(__PRETTY_FUNCTION__);
            return false;
          }
        }
      }

      bool wasInit(int flags){
        if(flags){
          return Mix_Init(0)&flags==flags;
        } else {
          return Mix_Init(0)!=0;
        }
      }
      void quit(){
        if(wasInit()){
          Mix_Quit();
        }
      }
      bool open(int frequency, Uint16 format, int channels, int chunksize){
        if(audio::init()&&init()){
          if(Mix_OpenAudio(frequency,format,channels,chunksize)==-1){
            Log::Audio.errorSDL(__PRETTY_FUNCTION__);
            return false;
          }
          return true;
        }
        return false;
      }
    }
  }
}

