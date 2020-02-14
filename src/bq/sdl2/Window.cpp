/*
 * Window.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: badquanta
 */
#include "Window.hpp"

#include "../sdl2/Subsystem.hpp"
#include <memory>
#include <map>
#include <mutex>

#include "Log.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
namespace bq {
  namespace sdl2 {
    Log &log = Log::Video;
    /** Used to ensure there is but one copy of each shared pointer. */
    WeakPtrCache<SDL_Window*, Window, SDL_Window*> Window::get_sptr(
        stdMakeShared<Window, SDL_Window*>);
    /**
     * """Use this function to create a 2D rendering context for a window.""" - SDL Wiki
     *
     * @param {int} idx=-1 index of rendering driver, -1 selects first supporting flags.
     * @param {Uint32} flags=0 combination of requested rendering flags.
     * @returns Renderer_sptr On success returns shared pointer to Renderer instance. On failure returns nullptr.
     *
     * @link https://wiki.libsdl.org/SDL_CreateRenderer?highlight=%28%5CbCategoryAPI%5Cb%29%7C%28SDLFunctionTemplate%29
     */
    Renderer_sptr Window::createRenderer(int idx,
        Uint32 flags) const {
      SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window,
          idx, flags);
      if (sdl_renderer) {
        fRenderer = Renderer::get_sptr(sdl_renderer, sdl_renderer);
      } else {
        log.errorSDL(__PRETTY_FUNCTION__);
        fRenderer = nullptr;
      }
      return fRenderer;
    }
    /**
     * """Use this function to get the renderer associated with a window.""" - SDL Wiki
     * for SDL_GetRenderer @link https://wiki.libsdl.org/SDL_GetRenderer?highlight=%28%5CbCategoryAPI%5Cb%29%7C%28SDLFunctionTemplate%29
     */
    Renderer_sptr Window::getRenderer() {
      if (!fRenderer) {
        SDL_Renderer *sdl_renderer = SDL_GetRenderer(sdl_window);
        if (sdl_renderer) {
          fRenderer = Renderer::get_sptr(sdl_renderer, sdl_renderer);
        } else {
          createRenderer();
        }
      }
      return fRenderer;
    }
    int Window::getCount(){
      return get_sptr.countAlive();
    }
    /**
     * TODO: Documentation for Window::create
     */
    Window_sptr Window::create(std::string_view t, int x, int y,
        int w, int h, Uint32 f) {
      SDL_Window *sdl_window = NULL;
      Window_sptr window = NULL;
      if (sdl2::init(SDL_INIT_VIDEO)) {
        sdl_window = SDL_CreateWindow(t.data(), x, y, w, h, f);
        if (sdl_window) {
          window = Window::get_sptr(sdl_window, sdl_window);
        } else {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      }
      return window;
    }
    /**
     * TODO: Document Window::create
     */
    Window_sptr Window::create(int w, int h, std::string_view t,
        Uint32 f) {
      return create(t, SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, w, h, f);
    }
    /**
     * TODO: Document Window::Window
     */
    Window::Window(SDL_Window *aWindow)
        : sdl_window(aWindow), fRenderer() {
      log.info(__PRETTY_FUNCTION__);
    }
    /**
     * TODO: Document Window::~Window
     */
    Window::~Window() {
      log.info(__PRETTY_FUNCTION__);
      // TODO Auto-generated destructor stub
    }
    /**
     * SDL_GetWindowSurface
     * @link https://wiki.libsdl.org/SDL_GetWindowSurface?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    Surface_sptr Window::getSurface() {
      SDL_Surface *sdl_surface = NULL;
      Surface_sptr surface = NULL;
      if ((sdl_surface = SDL_GetWindowSurface(sdl_window))) {
        surface = Surface::get_sptr(sdl_surface, sdl_surface);
      } else {
        log.errorSDL(__PRETTY_FUNCTION__);
      }
      return surface;
    }
    /**
     * like SDL_GetWindowID it returns 0 on error (or this->sdl_window was null)
     * it logs errors.
     * @link https://wiki.libsdl.org/SDL_GetWindowID?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    Uint32 Window::getID() {
      if (sdl_window) {
        Uint32 id = SDL_GetWindowID(sdl_window);
        if (id == 0) {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
        return id;
      }
      return 0;
    }
    /**
     * TODO: Document Window::updateSurface()
     */
    int Window::updateSurface() {
      return SDL_UpdateWindowSurface(sdl_window);
    }
    /**
     * TODO: Document Window::updateSurfaceRects()
     */
    int Window::updateSurfaceRects(SDL_Rect *rects,
        int numrects) {
      return SDL_UpdateWindowSurfaceRects(sdl_window, rects,
          numrects);
    }
    /**
     * SDL_GetWindowGrab
     * @link https://wiki.libsdl.org/SDL_GetWindowGrab?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    bool Window::getGrab() {
      return (
          sdl_window ?
              SDL_GetWindowGrab(sdl_window) == SDL_TRUE : false);
    }

    /**
     * SDL_GetWindowFromID
     * @link https://wiki.libsdl.org/SDL_GetWindowFromID?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    Window_sptr Window::getFromID(Uint32 id) {
      SDL_Window *sdl_window = SDL_GetWindowFromID(id);
      log.info("%s id = %d", __PRETTY_FUNCTION__, id);
      if (sdl_window) {
        return Window::get_sptr(sdl_window, sdl_window);
      } else {
        log.errorSDL(__PRETTY_FUNCTION__);
        return nullptr;
      }
    }
    /**
     * SDL_GetWindowFlags
     * @link https://wiki.libsdl.org/SDL_GetWindowFlags?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     * TODO: Possibly throttle?
     */
    Uint32 Window::getFlags() {
      if (sdl_window) {
        return SDL_GetWindowFlags(sdl_window);
      } else {
        log.debug("%s sdl_window is null", __PRETTY_FUNCTION__);
        return 0;
      }
    }

    /**
     * SDL_GetWindowDisplayIndex
     * @link https://wiki.libsdl.org/SDL_GetWindowDisplayIndex?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    int Window::getDisplayIndex() {
      if (sdl_window) {
        int idx = SDL_GetWindowDisplayIndex(sdl_window);
        if (idx < 0) {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
        return idx;
      } else {
        log.error("Window#sdl_window is null");
        return -1;
      }
    }
    /**
     * SDL_GetWindowData
     * @link https://wiki.libsdl.org/SDL_GetWindowData?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void* Window::getData(std::string_view name) {
      if (sdl_window) {
        return SDL_GetWindowData(sdl_window, name.data());
      } else {
        log.error("Window#sdl_window is null");
        return nullptr;
      }
    }
    /**
     * SDL_GetWindowBrightness
     * @link https://wiki.libsdl.org/SDL_GetWindowBrightness?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    float Window::getBrightness() {
      if (sdl_window) {
        return SDL_GetWindowBrightness(sdl_window);
      } else {
        log.error("Window#sdl_window is null");
        return -1.0;
      }
    }
    /**
     * SDL_GetWindowBorderSize
     * @link https://wiki.libsdl.org/SDL_GetWindowBordersSize?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    bool Window::getBorderSize(int &t, int &l, int &b, int &r) {
      if (sdl_window) {
        if (SDL_GetWindowBordersSize(sdl_window, &t, &l, &b, &r)
            == 0) {
          return true;
        } else {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      } else {
        t = 0;
        l = 0;
        b = 0;
        r = 0;
        log.error("Window#sdl_window is null");
      }
      return false;
    }
    /**
     * SDL_GetGrabbedWindow
     * @link https://wiki.libsdl.org/SDL_GetGrabbedWindow?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    Window_sptr Window::getGrabbed() {
      SDL_Window *sdl_window = SDL_GetGrabbedWindow();
      if (sdl_window) {
        return Window::get_sptr(sdl_window, sdl_window);
      } else {
        return nullptr;
      }
    }
    /**
     * """Use this function to get the size of a window's client area.""" - SDL Wiki
     * @link https://wiki.libsdl.org/SDL_GetWindowSize?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void Window::getSize(int &w, int &h) {
      if (sdl_window) {
        SDL_GetWindowSize(sdl_window, &w, &h);
      } else {
        w = 0;
        h = 0;
      }
    }
    /**
     * """Use this function to get the size of a window's client area.""" - SDL Wiki
     * just uses an SDL_Rect's `w` & `h` then returns said rect.
     * @link https://wiki.libsdl.org/SDL_GetWindowSize?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     **/
    SDL_Rect Window::getSize() {
      SDL_Rect size { 0, 0, 0, 0 };
      getSize(size.w, size.h);
      return size;
    }
    /**
     *
     */
    void Window::getMinimumSize(int &w, int &h) {
      if (sdl_window) {
        SDL_GetWindowMinimumSize(sdl_window, &w, &h);
      } else {
        w = 0;
        h = 0;
      }
    }
    /**
     * SDL_GetWindowMinimumSize
     * @link https://wiki.libsdl.org/SDL_GetWindowMinimumSize?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    SDL_Rect Window::getMinimumSize() {
      SDL_Rect size { 0, 0, 0, 0 };
      getMinimumSize(size.w, size.h);
      return size;
    }
    /**
     *
     */
    void Window::getMaximumSize(int &w, int &h) {
      if (sdl_window) {
        SDL_GetWindowMaximumSize(sdl_window, &w, &h);
      } else {
        w = 0;
        h = 0;
      }
    }
    /**
     * SDL_GetWindowMaximumSize
     * @link https://wiki.libsdl.org/SDL_GetWindowMaximumSize?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    SDL_Rect Window::getMaximumSize() {
      SDL_Rect size { 0, 0, 0, 0 };
      getMaximumSize(size.w, size.h);
      return size;
    }
    /**
     * SDL_GetWindowTitle
     * @link https://wiki.libsdl.org/SDL_GetWindowTitle?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    std::string_view Window::getTitle() {
      if (sdl_window) {
        return SDL_GetWindowTitle(sdl_window);
      } else {
        return nullptr;
      }
    }
    /**
     * SDL_SetWindowTitle
     * @link https://wiki.libsdl.org/SDL_GetWindowTitle?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    bool Window::setTitle(std::string_view title) {
      if (sdl_window) {
        SDL_SetWindowTitle(sdl_window, title.data());
        return true;
      } else {
        log.error("%s cannot set title of null sdl_window",
            __PRETTY_FUNCTION__);
        return false;
      }
    }
    /**
     * SDL_GetWindowPosition
     * @link https://wiki.libsdl.org/SDL_GetWindowPosition?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    bool Window::getPosition(int &x, int &y) {
      if (sdl_window) {
        SDL_GetWindowPosition(sdl_window, &x, &y);
        return true;
      } else {
        x = 0;
        y = 0;
        log.error("%s cannot get position of null sdl_window",
            __PRETTY_FUNCTION__);
        return false;
      }
    }
    /**
     * SDL_GetWindowPosition
     * @link https://wiki.libsdl.org/SDL_GetWindowPosition?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    SDL_Point Window::getPosition() {
      SDL_Point p { 0, 0 };
      getPosition(p.x, p.y);
      return p;
    }
    /**
     * SDL_SetWindowPosition
     * @link https://wiki.libsdl.org/SDL_SetWindowPosition
     */
    void Window::setPosition(int x, int y) {
      if (sdl_window) {
        SDL_SetWindowPosition(sdl_window, x, y);
        log.info("%s: x=%d, y=%d", __PRETTY_FUNCTION__, x, y);

      } else {
        log.error("%s cannot set position of null sdl_window",
            __PRETTY_FUNCTION__);

      }
    }
    /**
     * SDL_SetWindowPosition
     * @link https://wiki.libsdl.org/SDL_SetWindowPosition
     */
    void Window::setPosition(const SDL_Point& aPoint) {
      return setPosition(aPoint.x, aPoint.y);
    }
    /**
     * SDL_GetWindowPixelFormat
     * @link https://wiki.libsdl.org/SDL_GetWindowPixelFormat?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    Uint32 Window::getPixelFormat() {
      Uint32 format = SDL_PIXELFORMAT_UNKNOWN;
      if (sdl_window) {
        format = SDL_GetWindowPixelFormat(sdl_window);
        if (format == SDL_PIXELFORMAT_UNKNOWN) {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      } else {
        log.error("%s cannot get pixel format of null sdl_window",
            __PRETTY_FUNCTION__);
      }
      return format;
    }
    /**
     * SDL_GetWindowOpacity
     * @link https://wiki.libsdl.org/SDL_GetWindowOpacity?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    float Window::getOpacity() {
      float opacity = -1.0f;
      if (sdl_window) {
        SDL_GetWindowOpacity(sdl_window, &opacity);
        if (opacity < 0.0f) {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      } else {
        log.error("%s null sdl_window", __PRETTY_FUNCTION__);
      }
    }
    /**
     * SDL_HideWindow
     * @link https://wiki.libsdl.org/SDL_HideWindow?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void Window::hide() {
      if (sdl_window) SDL_HideWindow(sdl_window);
      else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
    }
    /**
     * SDL_MaximizeWindow
     * @link https://wiki.libsdl.org/SDL_MaximizeWindow?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void Window::maximize() {
      if (sdl_window) SDL_MaximizeWindow(sdl_window);
      else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
      ;
    }
    /**
     * SDL_MinimizeWindow
     * @link https://wiki.libsdl.org/SDL_MinizeWindow?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void Window::minimize() {
      if (sdl_window) SDL_MinimizeWindow(sdl_window);
      else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
    }
    /**
     *
     */
    void Window::raise() {
      if (sdl_window) SDL_RaiseWindow(sdl_window);
      else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
    }

    void Window::restore() {
      if (sdl_window) SDL_RestoreWindow(sdl_window);
      else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
    }

    bool Window::setBordered(SDL_bool b) {
      if (sdl_window) {
        SDL_SetWindowBordered(sdl_window, b);
        return true;
      } else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
      return false;
    }
    /**
     * """Use this function to set the brightness (gamma multiplier) for the display that owns a given window."""
     * `int SDL_SetWindowBrightness(SDL_Window* window,
     float       brightness)`
     * @link https://wiki.libsdl.org/SDL_SetWindowBrightness?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    bool Window::setBrightness(float b) {
      if (sdl_window) {
        if (SDL_SetWindowBrightness(sdl_window, b) == 0) {
          return true;
        } else log.errorSDL(__PRETTY_FUNCTION__);
      } else log.error("%s sdl_window is null",
          __PRETTY_FUNCTION__);
      return false;
    }
    /**
     * Use this function to associate an arbitrary named pointer with a window.
     * @link https://wiki.libsdl.org/SDL_SetWindowData?highlight=%28%5CbCategoryVideo%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     * @returns Returns the previous value associated with name.
     */
    void* Window::setData(std::string_view name, void *userdata) {
      if (sdl_window) {
        return SDL_SetWindowData(sdl_window, name.data(),
            userdata);
      } else {
        return nullptr;
      }
    }

    // TODO: SDL_SetWindowDisplayMode
    bool Window::setFullscreen(Uint32 flags) {
      if (sdl_window) {
        if (SDL_SetWindowFullscreen(sdl_window, flags) == 0) {
          log.info(__PRETTY_FUNCTION__);
          return true;
        } else {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      } else log.error("sdl_window is null");
      return false;
    }
    // TODO: bool setGammaRamp(SDL_Color&c);
    void Window::setGrab(SDL_bool b) {
      if (sdl_window) SDL_SetWindowGrab(sdl_window, b);
      else log.error("sdl_window is null");
    }
    // TODO: SDL_SetWindowHitTest
    void Window::setIcon(SDL_Surface*sdl_surface){
      if(sdl_window&&sdl_surface){
        SDL_SetWindowIcon(sdl_window,sdl_surface);
        log.info(__PRETTY_FUNCTION__);
      } else {
        if(!sdl_window)log.error("%: sdl_window is null",__PRETTY_FUNCTION__);
        if(!sdl_surface)log.error("%: sdl_surface is null",__PRETTY_FUNCTION__);
      }
    }
    void Window::setIcon(const Surface_sptr&s){
      setIcon(s->sdl_surface);
    }
    bool Window::setInputFocus(){
      if(sdl_window){
        if(SDL_SetWindowInputFocus(sdl_window)==0){
          log.info(__PRETTY_FUNCTION__);
          return true;
        } else {
          log.errorSDL(__PRETTY_FUNCTION__);
        }
      }
      return false;
    }
    void Window::setMaximumSize(int w, int h){
      if(sdl_window){
        SDL_SetWindowMaximumSize(sdl_window,w,h);
        log.info(__PRETTY_FUNCTION__);
      }
    }

    void Window::setMaximumSize(const SDL_Rect&r){
      setMaximumSize(r.w,r.h);
    }
    bool Window::setModalFor(SDL_Window*parent_window){
      if(sdl_window&&parent_window){
        if(SDL_SetWindowModalFor(sdl_window,parent_window)==0){
          log.info(__PRETTY_FUNCTION__);
          return true;
        } else log.errorSDL(__PRETTY_FUNCTION__);
      } else {
        if(!sdl_window)log.error("%s null sdl_window",__PRETTY_FUNCTION__);
        if(!parent_window)log.error("%s null parent_window",__PRETTY_FUNCTION__);
      }
      return false;
    }
    bool Window::setModalFor(const Window_sptr&w){
      return setModalFor(w->sdl_window);
    }
    bool Window::setOpacity(float opacity){
      if(sdl_window){
        if(SDL_SetWindowOpacity(sdl_window,opacity)==0){
          log.info(__PRETTY_FUNCTION__);
          return true;
        } else log.errorSDL(__PRETTY_FUNCTION__);
      }
      return false;
    }


    // START OF SDL_GetWindowFlag HELPER methods ---------------------------------------
    /**
     * This thing right here is just a convince so I don't have to type out the same boilerplate over and over again.
     */
#define WINDOW_FLAG_HELPER(flag, helpername) \
      bool Window::helpername(){\
        return (getFlags() & flag)==flag;\
      }
    /** Checks getFlags for SDL_WINDOW_FULLSCREEN */
    WINDOW_FLAG_HELPER(SDL_WINDOW_FULLSCREEN, isFullscreen)
    /** Checks getFlags for SDL_WINDOW_FULLSCREEN_DESKTOP */
    WINDOW_FLAG_HELPER(SDL_WINDOW_FULLSCREEN_DESKTOP,
        isFullscreenDesktop)
    /** Checks getFlags for SDL_WINDOW_OPENGL */
    WINDOW_FLAG_HELPER(SDL_WINDOW_OPENGL, isOpenGL)
    /** Checks getFlags for SDL_WINDOW_SHOWN */
    WINDOW_FLAG_HELPER(SDL_WINDOW_SHOWN, isShown)
    /** Checks getFlags for SDL_WINDOW_HIDDEN */
    WINDOW_FLAG_HELPER(SDL_WINDOW_HIDDEN, isHidden)
    /** Checks getFlags for SDL_WINDOW_BORDERLESS */
    WINDOW_FLAG_HELPER(SDL_WINDOW_BORDERLESS, isBorderless)
    /** Checks getFlags for SDL_WINDOW_RESIZABLE */
    WINDOW_FLAG_HELPER(SDL_WINDOW_RESIZABLE, isResizable)
    /** Checks getFlags for SDL_WINDOW_MINIMIZED */
    WINDOW_FLAG_HELPER(SDL_WINDOW_MINIMIZED, isMinimized)
    /** Checks getFlags for SDL_WINDOW_MAXIMIZED */
    WINDOW_FLAG_HELPER(SDL_WINDOW_MAXIMIZED, isMaximized)
    /** Checks getFlags for SDL_WINDOW_INPUT_GRABBED */
    WINDOW_FLAG_HELPER(SDL_WINDOW_INPUT_GRABBED, isInputGrabbed)
    /** Checks getFlags for SDL_WINDOW_INPUT_FOCUS */
    WINDOW_FLAG_HELPER(SDL_WINDOW_INPUT_FOCUS, isInputFocus)
    /** Checks getFlags for SDL_WINDOW_MOUSE_FOCUS */
    WINDOW_FLAG_HELPER(SDL_WINDOW_MOUSE_FOCUS, isMouseFocus)
    /** Checks getFlags for SDL_WINDOW_FOREIGN */
    WINDOW_FLAG_HELPER(SDL_WINDOW_FOREIGN, isForeign)
    /** Checks getFlags for SDL_WINDOW_ALLOW_HIGHDPI */
    WINDOW_FLAG_HELPER(SDL_WINDOW_ALLOW_HIGHDPI, allowsHighDPI)
    /** Checks getFlags for SDL_WINDOW_MOUSE_CAPTURE */
    WINDOW_FLAG_HELPER(SDL_WINDOW_MOUSE_CAPTURE, isMouseCapture)
    /** Checks getFlags for SDL_WINDOW_ALWAYS_ON_TOP */
    WINDOW_FLAG_HELPER(SDL_WINDOW_ALWAYS_ON_TOP, isAlwaysOnTop)
    /** Checks getFlags for SDL_WINDOW_SKIP_TASKBAR */
    WINDOW_FLAG_HELPER(SDL_WINDOW_SKIP_TASKBAR, doesSkipTaskbar)
    /** Checks getFlags for SDL_WINDOW_UTILITY */
    WINDOW_FLAG_HELPER(SDL_WINDOW_UTILITY, isUtility)
    /** Checks getFlags for SDL_WINDOW_TOOLTOP */
    WINDOW_FLAG_HELPER(SDL_WINDOW_TOOLTIP, isTooltip)
    /** Checks getFlags for SDL_WINDOW_POPUP_MENU */
    WINDOW_FLAG_HELPER(SDL_WINDOW_POPUP_MENU, isPopupMenu)
  // End of SDL_GetWindowFlags() helper methods ----------------------------
  /**
   * TODO: Document Window::
   */
  //Window::Window(const Window &other)
  //    : sdl_window(other.sdl_window) {
  //  // TODO Auto-generated constructor stub
  //}
  //Window::Window(Window &&other)
  //    : sdl_window(other.sdl_window) {
  //  // TODO Auto-generated constructor stub
  //}
  //Window& Window::operator=(const Window &other) {
  // TODO Auto-generated method stub
  //return *this;
  //}
  //Window& Window::operator=(Window &&other) {
  //   return *this; // TODO Auto-generated method stub
//    }
  }
} /* namespace bq::sdl2 */
