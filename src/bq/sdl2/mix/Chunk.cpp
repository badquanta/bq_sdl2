/*
 * Chunk.cpp
 *
 *  Created on: Feb 7, 2020
 *      Author: badquanta
 */

#include "Chunk.hpp"
#include "../Log.hpp"
#include "../mix.hpp"
#include "../audio.hpp"
namespace bq {
  namespace sdl2 {
    namespace mix {
      static Log& log=Log::Audio;
      WeakPtrCache<Mix_Chunk*,Chunk,Mix_Chunk*> Chunk::get_sptr(stdMakeShared<Chunk,Mix_Chunk*>);
      WeakPtrCache<std::string_view,Chunk,std::string_view> Chunk::load(
          [](std::string_view f)->Chunk_sptr{
        if(audio::init() && init()){
          Mix_Chunk* mix_chunk = Mix_LoadWAV(f.data());
          if(mix_chunk){
            return get_sptr(mix_chunk,mix_chunk);
          } else {
            log.errorMIX(__PRETTY_FUNCTION__);
          }
        }
        return nullptr;
      });

      Chunk::Chunk(Mix_Chunk*c):mix_chunk{c} {
        log.verbose(__PRETTY_FUNCTION__);
      }

      Chunk::~Chunk() {
        free();
        log.verbose(__PRETTY_FUNCTION__);
      }

      bool Chunk::free(){
        if(mayFree){
          if(mix_chunk){
            Mix_FreeChunk(mix_chunk);
            mix_chunk=nullptr;
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

      int Chunk::play(int channel, int loops){
        if(mix_chunk){
          int channel = Mix_PlayChannel(channel, mix_chunk, loops);
          if(channel>=0){
            log(__PRETTY_FUNCTION__);
            return channel;
          } else {
            log.errorMIX(__PRETTY_FUNCTION__);
          }
        } else {
          log.debug("%s: mix_chunk is null",__PRETTY_FUNCTION__);
        }
      }
      /**
      Chunk::Chunk(const Chunk &other) {
        Log::Audio.debug(__PRETTY_FUNCTION__);

      }

      Chunk::Chunk(Chunk &&other) {
        Log::Audio.debug(__PRETTY_FUNCTION__);

      }

      Chunk& Chunk::operator=(const Chunk &other) {
        Log::Audio.debug(__PRETTY_FUNCTION__);

      }

      Chunk& Chunk::operator=(Chunk &&other) {
        Log::Audio.debug(__PRETTY_FUNCTION__);
      }
    **/
    } /* namespace mix */
  } /* namespace sdl2 */
} /* namespace bq */
