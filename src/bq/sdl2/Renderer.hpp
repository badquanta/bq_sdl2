/*
 * Renderer.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_RENDERER_HPP_
#define SDL2_RENDERER_HPP_
#include <SDL2/SDL.h>

#include "shared_ptrs.hpp"
#include "../util/WeakPtrCache.hpp"
namespace bq {
namespace sdl2 {

class Renderer {
public:
  static WeakPtrCache<SDL_Renderer*,Renderer> get_sptr;
  Texture_sptr createTextureFromSurface(SDL_Surface *) const;
  Texture_sptr createTextureFromSurface(const Surface_sptr &) const;
  Texture_sptr loadTextureFromBMP(const std::string_view &) const;
  Texture_sptr loadTextureFromImage(const std::string_view &) const;
  /**Loads an image AND sets the color key of that image before returning
   * texture.**/
  Texture_sptr loadTextureFromImage(const std::string_view &, Uint8, Uint8,
                                       Uint8) const;
  bool setDrawColor(Uint8, Uint8, Uint8, Uint8) const;
  bool clear() const;
  bool copy(const Texture_sptr &t, const SDL_Point &at,
            const SDL_Rect *srclip = nullptr) const;
  bool copy(SDL_Texture *t, const SDL_Rect *s = nullptr,
            const SDL_Rect *d = nullptr) const;
  bool copy(const Texture_sptr &t, const SDL_Rect *s = nullptr,
            const SDL_Rect *d = nullptr) const;
  bool copyEx(SDL_Texture *t, const SDL_Rect *srcrect = nullptr,
              const SDL_Rect *dstrect = nullptr, const double angle = 0.0,
              const SDL_Point *center = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  bool copyEx(const Texture_sptr&, const SDL_Rect *srcrect = nullptr,
              const SDL_Rect *dstrect = nullptr, const double angle = 0.0,
              const SDL_Point *center = nullptr, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
  void present() const;
  bool fillRect(const SDL_Rect *) const;
  bool drawRect(const SDL_Rect *) const;
  bool drawLine(int, int, int, int) const;
  bool drawPoint(int, int) const;
  bool setViewport(const SDL_Rect *) const;
  Renderer(SDL_Renderer *);
  virtual ~Renderer();
  Renderer(const Renderer &other);
  Renderer(Renderer &&other);
  Renderer &operator=(const Renderer &other);
  Renderer &operator=(Renderer &&other);

protected:
  SDL_Renderer *fRenderer;
};

} /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_RENDERER_HPP_ */
