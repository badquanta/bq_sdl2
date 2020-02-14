/*
 * Haptic.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Haptic.hpp"
#include "Log.hpp"
namespace bq {
  namespace sdl2 {
    namespace haptic {

      bool init() {
        return (wasInit() || sdl2::init(SDL_INIT_HAPTIC));
      }
      bool wasInit() {
        return sdl2::wasInit(SDL_INIT_HAPTIC);
      }
      Haptic_sptr open(int idx) {
        if(init()){
          SDL_Haptic* sdl_haptic = SDL_HapticOpen(idx);
          if(sdl_haptic){
            return Haptic::get_sptr(sdl_haptic,sdl_haptic);
          } else {
            Log::Input.errorSDL(__PRETTY_FUNCTION__);
          }
        }
        return nullptr;
      }

    }


    WeakPtrCache<SDL_Haptic*,Haptic,SDL_Haptic*> Haptic::get_sptr(stdMakeShared<Haptic,SDL_Haptic*>);
    Haptic::Haptic(SDL_Haptic* h):sdl_haptic{h} {
      // TODO Auto-generated constructor stub

    }

    Haptic::~Haptic() {
      // TODO Auto-generated destructor stub
    }
  /** TODO: Remove or implement
   Haptic::Haptic(const Haptic &other) {
   // TODO Auto-generated constructor stub

   }

   Haptic::Haptic(Haptic &&other) {
   // TODO Auto-generated constructor stub

   }

   Haptic& Haptic::operator=(const Haptic &other) {
   // TODO Auto-generated method stub

   }

   Haptic& Haptic::operator=(Haptic &&other) {
   // TODO Auto-generated method stub

   }
   **/
  } /* namespace sdl2 */
} /* namespace bq */
