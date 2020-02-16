/*
 * ttf.hpp
 *
 *  Created on: Feb 5, 2020
 *      Author: badquanta
 */

#ifndef SDL2_TTF_HPP_
#define SDL2_TTF_HPP_
#include <SDL2/SDL_ttf.h>
#include <string_view>
#include "../shared_ptrs.hpp"
namespace bq {
  namespace sdl2 {
    class TTF {
      public:
        static bool init();
        static bool wasInit();
        static void quit();
        static const SDL_version* linked_version();
        static TTF_sptr get_sptr(TTF_Font*, int ptSize,
            int idx = 0);
        static TTF_sptr open(std::string_view path, int ptSize,
            int idx = 0);
        TTF(TTF_Font*,int,int);
        virtual ~TTF();
        void close();
        static  void byteSwappedUNICODE(int);
        virtual int getStyle();
        virtual void setStyle(int);
        virtual int height();
        virtual int ascent();
        virtual int descent();
        virtual int lineSkip();
        virtual long faces();
        virtual int faceIsFixedWidth();
        virtual std::string_view faceFamilyName();
        virtual std::string_view faceStyleName();
        virtual bool glyphMetrics(Uint16 ch, int *minx = nullptr,
            int *maxx = nullptr, int *miny = nullptr, int *maxy =
                nullptr, int *advance = nullptr);
        virtual bool sizeText(std::string_view,int*w,int*h);
        virtual bool sizeUTF8(std::string_view,int*w,int*h);
        //virtual bool sizeUNICODE16(std::u16string_view,int*w,int*h);
        virtual Surface_sptr renderText_Solid(std::string_view, SDL_Color fg);
        virtual Surface_sptr renderUTF8_Solid(std::string_view, SDL_Color fg);
        //virtual shares::Surface renderUNICODE16_Solid(std::u16string_view,SDL_Color fg);
        virtual Surface_sptr renderGlyph_Solid(Uint16 ch, SDL_Color fg);
        virtual Surface_sptr renderText_Shaded(std::string_view, SDL_Color fg,SDL_Color bg);
        virtual Surface_sptr renderUTF8_Shaded(std::string_view, SDL_Color fg,SDL_Color bg);
        //virtual shares::Surface renderUNICODE16_Shaded(std::u16string_view,SDL_Color fg,SDL_Color bg);
        virtual Surface_sptr renderGlyph_Shaded(Uint16 ch, SDL_Color fg,SDL_Color bg);
        virtual Surface_sptr renderText_Blended(std::string_view, SDL_Color fg);
        virtual Surface_sptr renderUTF8_Blended(std::string_view, SDL_Color fg);
        //virtual shares::Surface renderUNICODE16_Blended(std::u16string_view,SDL_Color fg);
        virtual Surface_sptr renderGlyph_Blended(Uint16 ch, SDL_Color fg);
        const int ptSize;
        const int index;
      protected:
        TTF_Font *fTTF_Font;
    };
  }
}
#endif /* SDL2_TTF_HPP_ */
