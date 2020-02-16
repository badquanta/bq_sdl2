/*
 * Renderer.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Renderer.hpp"

#include <map>
#include <memory>
#include <mutex>

#include "image.hpp"
#include "Log.hpp"
#include "Surface.hpp"
#include "Texture.hpp"
namespace bq {
namespace sdl2 {
  WeakPtrCache<SDL_Renderer*, Renderer> Renderer::get_sptr(stdOnCacheMissKey<SDL_Renderer*, Renderer>);
bool Renderer::setViewport(const SDL_Rect *rect) const {
  if (SDL_RenderSetViewport(fRenderer, rect) == 0) {
    Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
bool Renderer::fillRect(const SDL_Rect *rect) const {
  if (SDL_RenderFillRect(fRenderer, rect) == 0) {
    Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
bool Renderer::drawRect(const SDL_Rect *rect) const {
  if (SDL_RenderDrawRect(fRenderer, rect) == 0) {
    Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
bool Renderer::drawLine(int a, int b, int c, int d) const {
  if (SDL_RenderDrawLine(fRenderer, a, b, c, d) == 0) {
    Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
bool Renderer::drawPoint(int x, int y) const {
  if (SDL_RenderDrawPoint(fRenderer, x, y) == 0) {
    Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
void Renderer::present() const {
  // Log::Render.info(__PRETTY_FUNCTION__);
  SDL_RenderPresent(fRenderer);
}

bool Renderer::copyEx(SDL_Texture *t, const SDL_Rect *srcrect,
                      const SDL_Rect *dstrect,
                      const double angle,
                      const SDL_Point *center,
                      const SDL_RendererFlip flip) const {
  if (SDL_RenderCopyEx(fRenderer, t, srcrect, dstrect, angle, center, flip) ==
      0) {
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
bool Renderer::copyEx(const Texture_sptr &t,
                      const SDL_Rect *srcrect ,
                      const SDL_Rect *dstrect ,
                      const double angle ,
                      const SDL_Point *center ,
                      const SDL_RendererFlip flip) const {
  return (t && copyEx(t->fSDL_Texture, srcrect, dstrect, angle, center, flip));
}

bool Renderer::copy(SDL_Texture *t, const SDL_Rect *s,
                    const SDL_Rect *d) const {
  if (SDL_RenderCopy(fRenderer, t, s, d) == 0)
    return true;
  else {

    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}

bool Renderer::copy(const Texture_sptr &t, const SDL_Rect *sr,
                    const SDL_Rect *dr) const {
  if (t) {
    return copy(t->fSDL_Texture, sr, dr);
  } else {
    return false;
  }
}

bool Renderer::copy(const Texture_sptr &t, const SDL_Point &at,
                    const SDL_Rect *srcclip) const {
  if (t) {
    SDL_Rect atRect = {at.x, at.y, t->bounds.x, t->bounds.y};
    return copy(t, srcclip, &atRect);
  } else
    return false;
}

bool Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
  if (SDL_SetRenderDrawColor(fRenderer, r, g, b, a) == 0) {
    //Log::Render.info(__PRETTY_FUNCTION__);
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}

bool Renderer::clear() const {
  // Log::Render.info(__PRETTY_FUNCTION__);
  if (SDL_RenderClear(fRenderer) == 0) {
    return true;
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
    return false;
  }
}
Texture_sptr Renderer::createTextureFromSurface(SDL_Surface *surf) const {
  SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(fRenderer, surf);
  Texture_sptr texture{nullptr};
  if (sdl_texture) {
    Log::Render.info(__PRETTY_FUNCTION__);
    texture = Texture::get_sptr(sdl_texture);
    texture->bounds={0,0, surf->w, surf->h};
    texture->fRenderer=Renderer::get_sptr(this->fRenderer);
  } else {
    Log::Render.errorSDL(__PRETTY_FUNCTION__);
  }
  return texture;
}
/** Attempts to convert surface into texture for this renderer.**/
Texture_sptr
Renderer::createTextureFromSurface(const Surface_sptr &surf) const {
  if (surf)
    return createTextureFromSurface(surf->sdl_surface);
  else
    return nullptr;
}
/** Attempts to load BMP file from path & convert into texture.**/
Texture_sptr
Renderer::loadTextureFromBMP(const std::string_view &path) const {
  return createTextureFromSurface(Surface::loadBMP(path));
}
/** Attempts to load image file from path & convert into texture.**/
Texture_sptr
Renderer::loadTextureFromImage(const std::string_view &path) const {
  return createTextureFromSurface(image::load(path));
}
Texture_sptr Renderer::loadTextureFromImage(const std::string_view &path,
                                               Uint8 r, Uint8 g,
                                               Uint8 b) const {
  auto surface = image::load(path);
  if (surface) {
    surface->setColorKey(r, g, b);
  }
  return createTextureFromSurface(surface);
}
/** Construct an instance to manager a SDL_Renderer* pointer. **/
Renderer::Renderer(SDL_Renderer *aRenderer) : fRenderer(aRenderer) {
  Log::Render.info(__PRETTY_FUNCTION__);
}

Renderer::~Renderer() {
  if (fRenderer) {
    SDL_DestroyRenderer(fRenderer);
    Log::Render.info(__PRETTY_FUNCTION__);
  }
  Log::Render.info(__PRETTY_FUNCTION__);
  // TODO Auto-generated destructor stub
}


} /* namespace sdl2 */
} /* namespace bq */
