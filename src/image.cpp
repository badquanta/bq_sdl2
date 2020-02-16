/*
 * Image.cpp
 *
 *  Created on: Feb 2, 2020
 *      Author: badquanta
 */

#include "image.hpp"
#include "Log.hpp"
#include "Surface.hpp"
namespace bq { namespace sdl2 {namespace image{

bool init(Uint32 wanted){
  Uint32 current_init = IMG_Init(0);
  if((current_init&wanted)==wanted){
    return true;
  } else {
    current_init = IMG_Init(wanted|current_init);
    if((current_init&wanted)==wanted) return true;
  }
  return false;
}

bool wasInit(Uint32 wanted){
  Uint32 flags = IMG_Init(0);
  if(wanted!=0){
    return (flags & wanted)==wanted;
  } else {
    return flags != 0;
  }
}

bool quit(){
  IMG_Quit();
}

Surface_sptr load(std::string_view filename){
  SDL_Surface* sdl_surface= nullptr;
  Surface_sptr surface = nullptr;
  if(init()){
    sdl_surface = IMG_Load(filename.data());
    if(sdl_surface){
      surface = std::make_shared<Surface>(sdl_surface);
    } else {
      Log::System.error("Image load error: %s", IMG_GetError());
    }
  }
  return surface;

}

}
} /* namespace sdl2 */
} /* namespace bq */
