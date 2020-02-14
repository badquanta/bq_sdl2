/*
 * Mouse.hpp
 *
 *  Created on: Feb 6, 2020
 *      Author: badquanta
 */

#ifndef SDL2_MOUSECURSOR_HPP_
#define SDL2_MOUSECURSOR_HPP_
#include <SDL2/SDL.h>

#include "shared_ptrs.hpp"
#include <bq/WeakPtrCache.hpp>
namespace bq {
  namespace sdl2 {
    class MouseCursor {
      public:
        bool autoFree = true;
        SDL_Cursor* sdl_cursor;
        static WeakPtrCache<SDL_Cursor*, MouseCursor, SDL_Cursor*> get_sptr;
        MouseCursor(SDL_Cursor*);
        virtual ~MouseCursor();
        bool free();
        static bool capture(SDL_bool enabled);
        static MouseCursor_sptr createColorCursor(SDL_Surface*,int,int);
        static MouseCursor_sptr createColorCursor(const Surface_sptr&,int,int);
        static MouseCursor_sptr createCursor(const Uint8* data, const Uint8*mask,int w, int h, int hX, int hY);
        static MouseCursor_sptr createSystemCursor(SDL_SystemCursor id);
        static Uint32 state(int*x,int*y);
        static Uint32 state(SDL_Point&p);
        /** globally move mouse **/
        static bool warp(int x,int y);
        /** move mouse relative to window **/
        static void warpWindow(SDL_Window*,const SDL_Point&);
        /** move mouse relative to window **/
        static void warpWindow(const Window_sptr&, const SDL_Point&);
        /** move mouse relative to focused window **/
        static void warpFocused(const SDL_Point&);
        static Uint32 relativeState(int*x,int*y);
        static Uint32 relativeState(SDL_Point&p);
        static Window_sptr focused();
        static bool getRelativeMode();
        static bool setRelativeMode(SDL_bool s=SDL_TRUE);
        static void setCursor(SDL_Cursor*sdl_cursor);
        static void setCursor(const MouseCursor_sptr&cursor);
        static bool showCursor(int v=SDL_ENABLE);
        static bool cursorVisible();
        static bool hideCursor();


        MouseCursor(const MouseCursor &other)=delete;
        MouseCursor(MouseCursor &&other)=delete;
        MouseCursor& operator=(const MouseCursor &other)=delete;
        MouseCursor& operator=(MouseCursor &&other)=delete;
    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_MOUSECURSOR_HPP_ */
