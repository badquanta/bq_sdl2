/*
 * Surface.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */

#include "Surface.hpp"

#include <memory>
#include <map>
#include <mutex>

#include "Log.hpp"

namespace bq {
  namespace sdl2 {
    WeakPtrCache<SDL_Surface*, Surface, SDL_Surface*> Surface::get_sptr(stdMakeShared<Surface, SDL_Surface*>);
    /**
     * SDL_SetColorKey...
     * @link https://wiki.libsdl.org/SDL_SetColorKey?highlight=%28%5CbCategoryAPI%5Cb%29%7C%28SDLFunctionTemplate%29
     */
    bool Surface::setColorKey(int flag, Uint32 key) const {
      if (SDL_SetColorKey(sdl_surface, flag, key) == 0) {
        Log::Video.info(__PRETTY_FUNCTION__);
        return true;
      } else {
        Log::Video.errorSDL(__PRETTY_FUNCTION__);

        return false;
      }
    }
    /**
     * SDL_MapRGB
     */
    Uint32 Surface::mapRGB(Uint8 r, Uint8 g, Uint8 b) const {
      return SDL_MapRGB(sdl_surface->format, r, g, b);
    }
    /**
     * SDL_SetColorKey with R,G,B values; flag assumed to be SDL_TRUE.
     */
    bool Surface::setColorKey(Uint8 r, Uint8 g, Uint8 b) const {
      return setColorKey(SDL_TRUE, mapRGB(r, g, b));
    }

    /**
     *
     */
    Surface_sptr Surface::loadBMP(std::string_view path) {
      SDL_Surface *sdl_surface = SDL_LoadBMP(path.data());
      Surface_sptr surface = NULL;
      if (sdl_surface) {
        surface = get_sptr(sdl_surface, sdl_surface);

      } else {
        Log::Video.errorSDL(__PRETTY_FUNCTION__);
      }
      return (surface);
    }

    Surface::Surface(SDL_Surface *aSurface)
        : sdl_surface(aSurface) {
      Log::Video.info(__PRETTY_FUNCTION__);
    }

    Surface::~Surface() {
      if (SDL_QuitRequested()) {
        Log::Video.info(__PRETTY_FUNCTION__);
        SDL_FreeSurface(sdl_surface);
      }
      Log::Video.info(__PRETTY_FUNCTION__);
    }

    bool Surface::fillRect(const SDL_Rect *rect, Uint32 color) const{
      return SDL_FillRect(sdl_surface, rect, color);
    }

    bool Surface::fillRect(const SDL_Rect *rect, Uint8 r, Uint8 g,
        Uint8 b) const {
      return fillRect(rect, SDL_MapRGB(sdl_surface->format, r, g, b));
    }

    bool Surface::fillRect(const SDL_Rect *rect, Uint8 r, Uint8 g,
        Uint8 b, Uint8 a) const {
      return fillRect(rect,
          SDL_MapRGBA(sdl_surface->format, r, g, b, a));
    }
    /**
     *
     */
    bool Surface::blit(const SDL_Rect *srcrect, SDL_Surface *dst,
        SDL_Rect *dstrect) const {
      return (SDL_BlitSurface(sdl_surface, srcrect, dst, dstrect)
          == 0);
    }
    /**
     *
     */
    bool Surface::blit(const SDL_Rect *srcrect,
        const Surface_sptr& dst, SDL_Rect *dstrect)const {
      return (blit(srcrect, dst->sdl_surface, dstrect));
    }
    /**
     *
     */
    bool Surface::blitScaled(const SDL_Rect *srcrect,
        SDL_Surface *dst, SDL_Rect *dstrect) const {
      return (SDL_BlitScaled(sdl_surface, srcrect, dst, dstrect) == 0);
    }
    /**
     *
     */
    bool Surface::blitScaled(const SDL_Rect *srcrect,
        const Surface_sptr& dst, SDL_Rect *dstrect) const {
      return (blitScaled(srcrect, dst->sdl_surface, dstrect));
    }
    /**
     *
     */
    bool Surface::blitScaled(const Surface_sptr& dst) const {
      return (blitScaled(NULL, dst->sdl_surface,
          &dst->sdl_surface->clip_rect));
    }
/**
    Surface::Surface(const Surface &other)
        : sdl_surface(other.sdl_surface) {
      // TODO Auto-generated constructor stub

    }

    Surface::Surface(Surface &&other)
        : sdl_surface(other.sdl_surface) {// @suppress("No return")
      // TODO Auto-generated constructor stub
      // @suppress("No return")
    }

    Surface& Surface::operator=(const Surface &other) {// @suppress("No return")
      // TODO Auto-generated method stub
      // @suppress("No return")
    }

    Surface& Surface::operator=(Surface &&other) {// @suppress("No return")
      // TODO Auto-generated method stub
      // @suppress("No return")
    }
**/
  }
} /* namespace bq */
