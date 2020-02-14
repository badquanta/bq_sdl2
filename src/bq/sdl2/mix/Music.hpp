/*
 * Music.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_MIX_MUSIC_HPP_
#define SDL2_MIX_MUSIC_HPP_
#include <SDL2/SDL_mixer.h>
#include "shared_ptrs.hpp"
#include "../../util/WeakPtrCache.hpp"
namespace bq {
  namespace sdl2 {
    namespace mix {
      class Music {
        public:
          static WeakPtrCache<Mix_Music*,Music> get_sptr;
          static WeakPtrCache<std::string_view,Music> load;
          Mix_Music* mix_music;
          bool mayFree=true;
          static bool playing();
          static bool paused();
          static void resume();
          static void halt();
          static void pause();
          bool play(int loops=1);
          bool playLooped();
          Music(Mix_Music*);
          virtual ~Music();
          bool free();
          Music(const Music &other)=delete;
          Music(Music &&other)=delete;
          Music& operator=(const Music &other)=delete;
          Music& operator=(Music &&other)=delete;
      };

    } /* namespace mix */
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_MIX_MUSIC_HPP_ */
