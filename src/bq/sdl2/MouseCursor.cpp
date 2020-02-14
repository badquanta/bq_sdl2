/*
 * Mouse.cpp
 *
 *  Created on: Feb 6, 2020
 *      Author: badquanta
 */

#include "MouseCursor.hpp"

#include "Log.hpp"
#include <memory>
#include <map>
#include <mutex>

#include "Surface.hpp"
#include "Window.hpp"
namespace bq {
  namespace sdl2 {
    WeakPtrCache<SDL_Cursor*,MouseCursor> MouseCursor::get_sptr(stdMakeShared<SDL_Cursor*,MouseCursor>);

    MouseCursor::MouseCursor(SDL_Cursor *c)
        : sdl_cursor { c } {
      Log::Input.info(__PRETTY_FUNCTION__);
    }
    MouseCursor::~MouseCursor() {
      free();
    }
    MouseCursor_sptr MouseCursor::createColorCursor(SDL_Surface *surf,
        int x, int y) {
      MouseCursor_sptr cursor = nullptr;
      if (surf) {
        SDL_Cursor *sdl_cursor = SDL_CreateColorCursor(surf, x,
            y);
        if (sdl_cursor) {
          return MouseCursor::get_sptr(sdl_cursor);
        } else {
          Log::Video.errorSDL(__PRETTY_FUNCTION__);
        }
      }
      return cursor;
    }

    MouseCursor_sptr MouseCursor::createColorCursor(
        const Surface_sptr &surf, int x, int y) {
      if (surf) {
        return createColorCursor(surf->sdl_surface, x, y);
      }
      return nullptr;
    }
    MouseCursor_sptr MouseCursor::createCursor(const Uint8 *data,
        const Uint8 *mask, int w, int h, int hX, int hY) {
      SDL_Cursor *sdl_cursor = SDL_CreateCursor(data, mask, w, h,
          hX, hY);
      if (sdl_cursor) {
        return MouseCursor::get_sptr(sdl_cursor);
      } else {
        Log::Video.errorSDL(__PRETTY_FUNCTION__);
      }
      return nullptr;
    }

    MouseCursor_sptr MouseCursor::createSystemCursor(
        SDL_SystemCursor id) {
      SDL_Cursor *sdl_cursor = SDL_CreateSystemCursor(id);
      if (sdl_cursor) {
        return MouseCursor::get_sptr(sdl_cursor);
      }
    }

    bool MouseCursor::free() {
      if (sdl_cursor && autoFree) {
        SDL_FreeCursor(sdl_cursor);
        sdl_cursor = nullptr;
        return true;
      }
      return false;
    }
    Uint32 MouseCursor::state(int *x = NULL, int *y = NULL) {
      return SDL_GetGlobalMouseState(x, y);
    }
    Uint32 MouseCursor::state(SDL_Point &p) {
      return state(&p.x, &p.y);
    }
    Uint32 MouseCursor::relativeState(int *x = NULL, int *y = NULL) {
      return SDL_GetRelativeMouseState(x, y);
    }
    Uint32 MouseCursor::relativeState(SDL_Point &p) {
      return relativeState(&p.x, &p.y);
    }
    bool MouseCursor::getRelativeMode() {
      return SDL_GetRelativeMouseMode() == SDL_TRUE;
    }
    bool MouseCursor::setRelativeMode(SDL_bool s) {
      if (SDL_SetRelativeMouseMode(s) != 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
    }
    void MouseCursor::setCursor(SDL_Cursor*sdl_cursor){
      SDL_SetCursor(sdl_cursor);
    }
    void MouseCursor::setCursor(const MouseCursor_sptr&cursor){
      if(cursor){
        setCursor(cursor->sdl_cursor);
      }
    }
    bool MouseCursor::showCursor(int v){
      return SDL_ShowCursor(v)==SDL_ENABLE;
    }
    bool MouseCursor::cursorVisible(){
      return SDL_ShowCursor(SDL_QUERY)==SDL_ENABLE;
    }
    bool MouseCursor::hideCursor(){
      return SDL_ShowCursor(SDL_DISABLE);
    }

    bool MouseCursor::warp(int x,int y){
      if(SDL_WarpMouseGlobal(x,y)!=0){
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
      return true;
    }

    void MouseCursor::warpWindow(SDL_Window*w,const SDL_Point&p){
      SDL_WarpMouseInWindow(w,p.x,p.y);
    }
    void MouseCursor::warpWindow(const Window_sptr&w,const SDL_Point&p){
      warpWindow(w?w->sdl_window:nullptr,p);
    }
    void MouseCursor::warpFocused(const SDL_Point&p){
      warpWindow(nullptr,p);
    }

    Window_sptr MouseCursor::focused() {
      SDL_Window *sdl_window = SDL_GetMouseFocus();
      if (sdl_window) {
        return Window::get_sptr(sdl_window);
      }
    }

    bool MouseCursor::capture(SDL_bool enabled) {
      if (SDL_CaptureMouse(enabled) != 0) {
        Log::Input.error(__PRETTY_FUNCTION__);
      }
      return true;
    }
  /**
   MouseCursor::Mouse(const Mouse &other) {
   // TODO Auto-generated constructor stub

   }

   MouseCursor::Mouse(Mouse &&other) {
   // TODO Auto-generated constructor stub

   }

   Mouse& MouseCursor::operator=(const Mouse &other) {
   // TODO Auto-generated method stub

   }

   Mouse& MouseCursor::operator=(Mouse &&other) {
   // TODO Auto-generated method stub

   }**/

  } /* namespace sdl2 */
} /* namespace bq */
