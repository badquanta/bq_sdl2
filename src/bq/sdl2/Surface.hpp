/*
 * Surface.hpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */

#ifndef SURFACE_HPP_
#define SURFACE_HPP_
#include <SDL2/SDL.h>
#include <bq/WeakPtrCache.hpp>
#include "shared_ptrs.hpp"
namespace bq {
  namespace sdl2 {
    class Surface {
        friend Window;
        friend Renderer;
      public:
        static WeakPtrCache<SDL_Surface*,Surface> get_sptr;
        static Surface_sptr loadBMP(std::string_view path);
        Surface(SDL_Surface *aSurface);
        virtual ~Surface();
        bool fillRect(const SDL_Rect *rect, Uint32 color)const;
        bool fillRect(const SDL_Rect *rect, Uint8 r, Uint8 g,
            Uint8 b, Uint8 a)const;
        bool fillRect(const SDL_Rect *rect, Uint8 r, Uint8 g,
            Uint8 b)const;
        bool blit(const SDL_Rect *srcrect, SDL_Surface *dst,
            SDL_Rect *dstrect)const;
        bool blit(const SDL_Rect *srcrect, const Surface_sptr& dst,
            SDL_Rect *dstrect)const;
        bool blitScaled(const SDL_Rect *srcrect, SDL_Surface *dst,
            SDL_Rect *dstrect)const;
        bool blitScaled(const SDL_Rect *srcrect,
            const Surface_sptr& dst, SDL_Rect *dstrect)const;
        bool blitScaled(const Surface_sptr& dst)const;
        Uint32 mapRGB(Uint8, Uint8, Uint8)const;
        bool setColorKey(int flag, Uint32 key)const;
        bool setColorKey(Uint8, Uint8, Uint8)const;
        SDL_Surface *sdl_surface;
      protected:

        Surface(const Surface &other)=delete;
        Surface(Surface &&other)=delete;
        Surface& operator=(const Surface &other)=delete;
        Surface& operator=(Surface &&other)=delete;

    };

  } /* namespace bq */
}
#endif /* SURFACE_HPP_ */
