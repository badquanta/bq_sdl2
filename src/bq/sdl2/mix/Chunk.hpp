/*
 * Chunk.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_MIX_CHUNK_HPP_
#define SDL2_MIX_CHUNK_HPP_
#include "shared_ptrs.hpp"
#include "../../util/WeakPtrCache.hpp"
#include <SDL2/SDL_mixer.h>
namespace bq {
  namespace sdl2 {
    namespace mix {

      class Chunk {
        public:
          static WeakPtrCache<Mix_Chunk*,Chunk> get_sptr;
          static WeakPtrCache<std::string_view,Chunk> load;
          Mix_Chunk* mix_chunk;
          bool mayFree=true;
          Chunk(Mix_Chunk*);
          virtual ~Chunk();
          bool free();
          int play(int channel=-1, int loops=1);
          Chunk(const Chunk &other)=delete;
          Chunk(Chunk &&other)=delete;
          Chunk& operator=(const Chunk &other)=delete;
          Chunk& operator=(Chunk &&other)=delete;
      };

    } /* namespace mix */
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_MIX_CHUNK_HPP_ */
