/*
 * Window.hpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */

#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include <SDL2/SDL.h>
#include <memory>
#include <string_view>

#include "shared_ptrs.hpp"
#include "../util/WeakPtrCache.hpp"
namespace bq {
  namespace sdl2 {
    /**
     * TODO: SDL_GetWindowGammaRamp
     * TODO: SDL_GetWindowDisplayMode
     * @link https://wiki.libsdl.org/SDL_GetWindowDisplayMode?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     * TODO: SDL_GetWindowDisplayMode
     *         // TODO: SDL_Rect getBorderSize();
     // I don't think a SDL_Rect is the right type for this.
     // TODO: SDL_GetVideoDriver()
     // TODO: SDL_GetNumVideoDrivers();
     // TODO: SDL_GetNumVideoDisplays();
     // TODO: SDL_GetNumDisplayModes()
     // TODO: SDL_GetDisplayUsableBounds();
     // TODO: SDL_GetDisplayName
     // TODO: SDL_GetDisplayMode
     // TODO: SDL_GetDisplayDPI
     // TODO: SDL_GetDisplayBounds
     // TODO: SDL_GetDesktopDisplayMode
     // TODO: SDL_GetCurrentVideoDriver
     // TODO: SDL_GetCurrentDisplayMode
     // TODO: SDL_GetClosestDisplayMode
     // TODO: SDL_IsScreenSaverEnabled (different spot?)
     * TODO: SDL_GetWindowWMInfo
     * @link https://wiki.libsdl.org/SDL_GetWindowWMInfo?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     *
     */
    class Window {
      public: // TODO make sdl_window reference private/protected.
        SDL_Window *sdl_window;
        Window(SDL_Window *aWindow);
        virtual ~Window();
        // Static global caches of Window instances to weak/shared pointers.
        static WeakPtrCache<SDL_Window*, Window> get_sptr;
        // ------------------------------------------------------------
      public: // Instance creators
        static int getCount();
        //static Window_sptr get_sptr(SDL_Window*);
        static Window_sptr create(std::string_view title, int x =
            0, int y = 0, int w = 0, int h = 0, Uint32 flags = 0);
        static Window_sptr create(int w, int h,
            ::std::string_view title, Uint32 flags = 0);
        Renderer_sptr createRenderer(int idx=-1,
                Uint32 flags=0) const;
        // -----------------------------------------------------------
      public: // Instance retrievers; may return null sometimes; but that is not an error.
        static Window_sptr getFromID(Uint32 id);
        static Window_sptr getGrabbed();
        // ------------------------------------------------------------
      public: // window actions
        void hide();
        bool isShown();
        bool isHidden();
        void maximize();
        void minimize();
        void raise();
        void restore();
        int updateSurface();
        int updateSurfaceRects(SDL_Rect *rects, int numrects);
        // ------------------------------------------------------------
      public: // read-only property getters
        Surface_sptr getSurface();
        Renderer_sptr getRenderer();
        Uint32 getID();
        Uint32 getPixelFormat();
        int getDisplayIndex();
        // ------------------------------------------------------------
      public: // write-only property setters: `Icon` & `ModalFor`
        void setIcon(SDL_Surface*);
        void setIcon(const Surface_sptr&);
        bool setModalFor(SDL_Window*);
        bool setModalFor(const Window_sptr&);
        // ------------------------------------------------------------
      public: // position getter/setters
        bool getPosition(int &x, int &y);
        SDL_Point getPosition();
        void setPosition(int x, int y);
        void setPosition(const SDL_Point&);
        // ------------------------------------------------------------
      public: // sizes getter/setters: `Size`, `MinimumSize`, `MaximumSize`, `Fullscreen`
        void getSize(int &w, int &h);
        SDL_Rect getSize();
        bool setSize(int w, int h);
        bool setSize(SDL_Rect);
        void getMinimumSize(int &w, int &h);
        SDL_Rect getMinimumSize();
        bool setMinimumSize(int w, int h);
        bool setMinimumSize(const SDL_Rect&);
        void getMaximumSize(int &w, int &h);
        SDL_Rect getMaximumSize();
        void setMaximumSize(int w, int h);
        void setMaximumSize(const SDL_Rect&);
        bool setFullscreen(Uint32 flags = SDL_WINDOW_FULLSCREEN);
        bool setFullscreenDesktop();
        bool exitFullscreen();
        bool isFullscreen();
        bool isFullscreenDesktop();
        // ------------------------------------------------------------
      public: // title string property get/set
        std::string_view getTitle();
        bool setTitle(std::string_view title);
        // ------------------------------------------------------------
      public: // associated user data
        void* setData(std::string_view name, void *userdata);
        void* getData(std::string_view name);
        // ------------------------------------------------------------
      public: // opacity: AKA: how much you can see through it. 1.0 == NOT SEE THROUGH. 0.0 == INVISIBLE
        float getOpacity();
        bool setOpacity(float opacity = 1.0f);
        // ------------------------------------------------------------
      public: // brightness: 1.0==normal 0.0==DARK/BLACK
        float getBrightness();
        bool setBrightness(float b = 1.0);
        // ------------------------------------------------------------
      public: // define if window has a borde
        bool isBorderless();
        bool getBordered();
        bool setBordered(SDL_bool b = SDL_TRUE);
        bool getBorderSize(int &t, int &l, int &b, int &r);
        // ------------------------------------------------------------
      public: // All instance `getter` functions
        bool getGrab();
        bool isGrab();
        void setGrab(SDL_bool b = SDL_TRUE);
        bool isInputGrabbed();
        bool isInputFocus();
        bool isMouseFocus();
        bool setInputFocus();
        // ------------------------------------------------------------
      public: // getFlags & other various flag checking helpers.
        Uint32 getFlags();
        //flag helper functions start
        bool isOpenGL();
        bool isResizable();
        bool isMinimized();
        bool isMaximized();
        bool isForeign();
        bool allowsHighDPI();
        bool isMouseCapture();
        bool isAlwaysOnTop();
        bool doesSkipTaskbar();
        bool isUtility();
        bool isTooltip();
        bool isPopupMenu();
        //flag helper functions end

        // TODO: SDL_SetWindowDisplayMode

        // TODO: bool setGammaRamp(SDL_Color&c);

        // TODO: SDL_SetWindowHitTest

      private:

        mutable Renderer_sptr fRenderer;

      protected:
        Window(const Window &other) = delete;
        Window(Window &&other) = delete;
        Window& operator=(const Window &other) = delete;
        Window& operator=(Window &&other) = delete;
    };
  }
} /* namespace bq */

#endif /* WINDOW_HPP_ */
