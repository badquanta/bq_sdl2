/*
 * ttf.cpp
 *
 *  Created on: Feb 5, 2020
 *      Author: badquanta
 */
#include "TTF.hpp"

#include <memory>
#include <mutex>
#include <map>

#include "../Log.hpp"
#include "../Surface.hpp"
namespace bq {
  namespace sdl2 {
    TTF_sptr TTF::get_sptr(TTF_Font *f, int ptSize, int idx) {
      static std::map<TTF_Font*, std::weak_ptr<TTF>> cache;
      static std::mutex m;
      std::lock_guard < std::mutex > hold(m);
      auto sp = cache[f].lock();
      if (!sp) cache[f] = sp = std::make_shared<TTF>(f,ptSize,idx);
      return sp;
    }

    TTF::TTF(TTF_Font*f,int p, int idx):
        fTTF_Font{f},
        ptSize{p},
        index{idx}
    {

    }
    TTF::~TTF(){
      this->close();
    }
    void TTF::byteSwappedUNICODE(int swapped) {
      TTF_ByteSwappedUNICODE(swapped);
    }
    /**
     *
     */
    int TTF::getStyle() {
      return fTTF_Font ? TTF_GetFontStyle(fTTF_Font) : 0;
    }
    /**
     *
     */
    void TTF::setStyle(int s) {
      if (fTTF_Font) TTF_SetFontStyle(fTTF_Font, s);
    }
    /**
     *
     */
    int TTF::height() {
      return fTTF_Font ? TTF_FontHeight(fTTF_Font) : 0;
    }
    /**
     *
     */
    int TTF::ascent() {
      return fTTF_Font ? TTF_FontAscent(fTTF_Font) : 0;
    }
    /**
     *
     */
    int TTF::descent() {
      return fTTF_Font ? TTF_FontDescent(fTTF_Font) : 0;
    }
    /**
     *
     */
    int TTF::lineSkip() {
      return fTTF_Font ? TTF_FontLineSkip(fTTF_Font) : 0;
    }
    /**
     *
     */
    long TTF::faces() {
      return fTTF_Font ? TTF_FontFaces(fTTF_Font) : 0;
    }
    /**
     *
     */
    int TTF::faceIsFixedWidth() {
      return fTTF_Font ? TTF_FontFaceIsFixedWidth(fTTF_Font) : 0;
    }
    /**
     *
     */
    std::string_view TTF::faceFamilyName() {
      return fTTF_Font ? TTF_FontFaceFamilyName(fTTF_Font) : "";
    }
    /**
     *
     */
    std::string_view TTF::faceStyleName() {
      return fTTF_Font ? TTF_FontFaceStyleName(fTTF_Font) : "";
    }
    /**
     *
     */
    bool TTF::glyphMetrics(Uint16 ch, int *minx, int *maxx,
        int *miny, int *maxy, int *advance) {
      return fTTF_Font
          && (TTF_GlyphMetrics(fTTF_Font, ch, minx, maxx, miny,
              maxy, advance) == 0);
    }
    /**
     *
     */
    bool TTF::sizeText(std::string_view str, int *w, int *h) {
      return fTTF_Font
          && (TTF_SizeText(fTTF_Font, str.data(), w, h) == 0);
    }
    /**
     *
     */
    bool TTF::sizeUTF8(std::string_view str, int *w, int *h) {
      return fTTF_Font
          && (TTF_SizeUTF8(fTTF_Font, str.data(), w, h) == 0);
    }

    /**
     *
     */
    Surface_sptr TTF::renderText_Solid(std::string_view str,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderText_Solid(fTTF_Font, str.data(),
          fg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderUTF8_Solid(std::string_view str,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderUTF8_Solid(fTTF_Font, str.data(),
          fg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderGlyph_Solid(Uint16 ch,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderGlyph_Solid(fTTF_Font, ch, fg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderText_Shaded(std::string_view str,
        SDL_Color fg, SDL_Color bg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderText_Shaded(fTTF_Font,
          str.data(), fg, bg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderUTF8_Shaded(std::string_view str,
        SDL_Color fg, SDL_Color bg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderUTF8_Shaded(fTTF_Font,
          str.data(), fg, bg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderGlyph_Shaded(Uint16 ch,
        SDL_Color fg, SDL_Color bg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderGlyph_Shaded(fTTF_Font, ch, fg,
          bg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderText_Blended(std::string_view str,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderText_Blended(fTTF_Font,
          str.data(), fg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }
    /**
     *
     */
    Surface_sptr TTF::renderUTF8_Blended(std::string_view str,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *s = TTF_RenderUTF8_Blended(fTTF_Font,
          str.data(), fg);
      if (s) return Surface::get_sptr(s,s);
      else Log::Render.errorTTF(__PRETTY_FUNCTION__);
      return nullptr;
    }

    /**
     *
     */
    Surface_sptr TTF::renderGlyph_Blended(Uint16 ch,
        SDL_Color fg) {
      if (!fTTF_Font) return nullptr;
      SDL_Surface *sdl_surface = TTF_RenderGlyph_Blended(
          fTTF_Font, ch, fg);
      if (sdl_surface) {
        return Surface::get_sptr(sdl_surface, sdl_surface);
      } else {
        Log::Render.errorTTF(__PRETTY_FUNCTION__);
        return nullptr;
      }
    }
    /**
     *
     */
    TTF_sptr TTF::open(std::string_view path, int ptSize,
        int idx) {
      if (init()) {
        TTF_Font *ttf_font = TTF_OpenFontIndex(path.data(),
            ptSize, idx);
        if (ttf_font) {
          return get_sptr(ttf_font, ptSize);
        } else {
          Log::System.errorTTF(__PRETTY_FUNCTION__);
        }
      }
      return nullptr;
    }
    /**
     *
     */
    void TTF::close() {
      if (fTTF_Font) {
        Log::System.info("TTF::close()");
        TTF_CloseFont(fTTF_Font);
        fTTF_Font = nullptr;
      }
    }
    /**
     *
     */
    const SDL_version* TTF::linked_version() {
      return TTF_Linked_Version();
    }

    /**
     *
     */

    bool TTF::init() {
      if (!wasInit()) {
        if (TTF_Init() == 0) {
          Log::System.info("TTF Init");
          return true;
        } else {
          Log::System.errorTTF(__PRETTY_FUNCTION__);
          return false;
        }
      } else return true;
    }
    /**
     *
     */
    bool TTF::wasInit() {
      return TTF_WasInit();
    }
    /**
     *
     */
    void TTF::quit() {
      Log::System.info(__PRETTY_FUNCTION__);
      return TTF_Quit();
    }
  }
}
