/*
 * Texture.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Texture.hpp"

#include <memory>
#include <map>
#include <mutex>

#include "Log.hpp"
#include "Renderer.hpp"
namespace bq {
  namespace sdl2 {
    WeakPtrCache<SDL_Texture*,Texture> Texture::get_sptr(stdMakeShared<SDL_Texture*,Texture>);
    bool Texture::setBlendMode(SDL_BlendMode m) const {
      if (SDL_SetTextureBlendMode(fSDL_Texture, m) == 0) {
        Log::Render.info(__PRETTY_FUNCTION__);
        return true;
      } else {
        Log::Render.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
    }
    bool Texture::setAlphaMod(Uint8 a) const {
      if (SDL_SetTextureAlphaMod(fSDL_Texture, a) == 0) {
        Log::Render.info(__PRETTY_FUNCTION__);
        return true;
      } else {
        Log::Render.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
    }
    bool Texture::setColorMod(const Uint8 r, const Uint8 g,
        const Uint8 b) const {
      if (SDL_SetTextureColorMod(fSDL_Texture, r, g, b) == 0) {
        Log::Render.info(__PRETTY_FUNCTION__);
        return true;
      } else {
        Log::Render.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
    }
    bool Texture::render() const {
      return (fSDL_Texture && fRenderer)
          && (fRenderer->copy(fSDL_Texture));
    }
    bool Texture::render(const SDL_Point &p) const {
      SDL_Rect clip = bounds;
      SDL_Rect at = clip;
      at.x = p.x;
      at.y = p.y;
      return (fSDL_Texture && fRenderer)
          && (fRenderer->copy(fSDL_Texture, &clip, &at));
    }
    bool Texture::render(const SDL_Rect &dstrect) const {
      return (fSDL_Texture && fRenderer)
          && (fRenderer->copy(fSDL_Texture, nullptr, &dstrect));
    }
    bool Texture::render(const SDL_Point &p, double a,
        SDL_RendererFlip f) const {
      SDL_Rect clip = bounds;
      SDL_Rect at = clip;
      at.x = p.x;
      at.y = p.y;
      return (fSDL_Texture && fRenderer)
          && (fRenderer->copyEx(fSDL_Texture, &clip, &at, a,
              nullptr, f));
    }

    Texture::Texture(SDL_Texture *t)
        : fSDL_Texture(t) {
      Log::Render.info(__PRETTY_FUNCTION__);
    }

    Texture::~Texture() {
      Log::Render.info(__PRETTY_FUNCTION__);
    }

    Texture::Texture(const Texture &other)
        : bounds(other.bounds), fSDL_Texture(other.fSDL_Texture), fRenderer(
            other.fRenderer) {
      // TODO Auto-generated constructor stub

    }

    Texture::Texture(Texture &&other)
        : bounds(other.bounds), fSDL_Texture(other.fSDL_Texture), fRenderer(
            other.fRenderer) {
      // TODO Auto-generated constructor stub
    }

    Texture& Texture::operator=(const Texture &other) {
      // TODO Auto-generated method stub
      this->bounds = other.bounds;
      this->fSDL_Texture = other.fSDL_Texture;
      return (*this);

    }

    Texture& Texture::operator=(Texture &&other) { // @suppress("No return")
      // TODO Auto-generated method stub
      this->bounds = other.bounds;
      this->fSDL_Texture = other.fSDL_Texture;
      return (*this);
    }

  } /* namespace sdl2 */
} /* namespace bq */
