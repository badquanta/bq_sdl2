/*
 * Texture.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_TEXTURE_HPP_
#define SDL2_TEXTURE_HPP_
#include <SDL2/SDL.h>

#include "shared_ptrs.hpp"
//#include "../pd/Sprite.hpp"
#include <bq/WeakPtrCache.hpp>
#include "Renderer.hpp"
namespace bq {
  namespace sdl2 {
    class Texture {
      friend Renderer;
      public:
        /**Ensure there is but one shared_ptr per SDL_Texture&**/
        static WeakPtrCache<SDL_Texture*, Texture, SDL_Texture*> get_sptr;
        /**Encode the "bounds" of this texture, x==w & y==h**/
        SDL_Rect bounds;

        bool setColorMod(const Uint8, const Uint8, const Uint8) const  ;
        bool setBlendMode(SDL_BlendMode m) const;
        bool setAlphaMod(Uint8) const;
        /** Just copies the texture to the renderer; fills renderer.**/
        bool render() const;
        /** No-scale/flip/rotation, just copy texture at renderer X&Y.**/
        bool render(const SDL_Point&) const;
        /** Scale texture to dstrect **/
        bool render(const SDL_Rect&) const;
        /** Scale,rotate,flip at renderer X&Y **/
        bool render(const SDL_Point&, double angle, SDL_RendererFlip=SDL_FLIP_NONE) const;
        //Texture(SDL_Texture*,int,int,const Renderer_sptr&);
        Texture(SDL_Texture*);
        virtual ~Texture();
        Texture(const Texture &other);
        Texture(Texture &&other);
        Texture& operator=(const Texture &other);
        Texture& operator=(Texture &&other);
      protected:
        SDL_Texture*fSDL_Texture;
        Renderer_sptr fRenderer;

      public:

    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_TEXTURE_HPP_ */
