/*
 * shared_ptrs.hpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#ifndef SDL2_MIX_SHARED_PTRS_HPP_
#define SDL2_MIX_SHARED_PTRS_HPP_
#include <memory>
namespace bq {
  namespace sdl2 {
    namespace mix {
      class Chunk;
      typedef std::shared_ptr<Chunk> Chunk_sptr;
      class Music;
      typedef std::shared_ptr<Music> Music_sptr;
    }
  }
}


#endif /* SDL2_MIX_SHARED_PTRS_HPP_ */
