/*
 * Music.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#include "Music.hpp"
#include "../Log.hpp"
#include "../mix.hpp"
namespace bq {
  namespace sdl2 {
    namespace mix {
      static Log& log=Log::Audio;
      WeakPtrCache<Mix_Music*,Music> Music::get_sptr(stdMakeShared<Mix_Music*,Music>);
      WeakPtrCache<std::string_view,Music> Music::load([](std::string_view f)-> mix::Music_sptr {
        if(init()){
          Mix_Music* mix_music = Mix_LoadMUS(f.data());
          if(mix_music){
            return get_sptr(mix_music);
          } else {
            log.errorMIX(__PRETTY_FUNCTION__);
          }

        }
        return nullptr;
      });

      Music::Music(Mix_Music*mm):mix_music{mm} {
        log.info(__PRETTY_FUNCTION__);
      }

      Music::~Music() {
        free();
        log.info(__PRETTY_FUNCTION__);
      }
      bool Music::free(){
        if(mayFree){
          if(mix_music){
            Mix_FreeMusic(mix_music);
            mix_music=nullptr;
            log(__PRETTY_FUNCTION__);
            return true;
          } else {
            log.verbose("%s already freed.",__PRETTY_FUNCTION__);
          }
        } else {
          log.info("%s: not freed because mayFree is false.",__PRETTY_FUNCTION__);
        }
        return false;
      }
      bool Music::play(int loops){
        if(mix_music){
          if(Mix_PlayMusic(mix_music,loops)==0){
            log(__PRETTY_FUNCTION__);
            return true;
          } else {
            log.errorMIX(__PRETTY_FUNCTION__);
          }
        } else log.debug("%s: mix_music is null",__PRETTY_FUNCTION__);
        return false;
      }
      bool Music::playLooped(){
        return play(-1);
      }
      bool Music::playing(){
        return Mix_PlayingMusic()==1;
      }
      bool Music::paused(){
        return Mix_PausedMusic()==1;
      }
      void Music::pause(){
        log.verbose(__PRETTY_FUNCTION__);
        Mix_PauseMusic();
      }
      void Music::resume(){
        log.verbose(__PRETTY_FUNCTION__);
        Mix_ResumeMusic();
      }
      void Music::halt(){
        log.verbose(__PRETTY_FUNCTION__);
        if(Mix_HaltMusic()!=0)log.error("Huh? Should have returned 0.");
      }

/**
      Music::Music(const Music &other) {
        // TODO Auto-generated constructor stub

      }

      Music::Music(Music &&other) {
        // TODO Auto-generated constructor stub

      }

      Music& Music::operator=(const Music &other) {
        // TODO Auto-generated method stub

      }

      Music& Music::operator=(Music &&other) {
        // TODO Auto-generated method stub

      }
**/
    } /* namespace mix */
  } /* namespace sdl2 */
} /* namespace bq */
