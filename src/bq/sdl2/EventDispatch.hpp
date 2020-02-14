/*
 * Events.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_EVENTDISPATCH_HPP_
#define SDL2_EVENTDISPATCH_HPP_
#include <SDL2/SDL.h>
#include <functional>
#include <list>
namespace bq {
  namespace sdl2 {
    namespace event {
      void pump(void);
      //int  peep(SDL_Event*, int num, SDL_eventaction action, Uint32 minType, Uint32 maxType);
      bool hasAny(Uint32 minType=SDL_FIRSTEVENT, Uint32 maxType=SDL_LASTEVENT);
      bool has(Uint32 type);
      bool poll(SDL_Event*);
      bool push(SDL_Event*);
      bool enabled(Uint32 type);
      bool enable(Uint32 type);
      bool disable(Uint32 type);

      //as "register" is a reserved word, I'm calling it declare instead.
      Uint32 declare(int);

    }
    bool pollEvent(SDL_Event *e = NULL);
    /** An event handler is a very simple function; meant to be
     * provides as a lambda.  It simply gets called with a reference
     * to an SDL_Event structure.  If the handler claims to have
     * "handled" the event; and no further handling is needed, it should
     * return true to prevent further event processing. Otherwise it should
     * return false and the event will be continued to be processed by dispatchers.
     */
    typedef std::function<bool(const SDL_Event&)> EventHandler;
    /** a standard linked list of event handlers, double so we can add to back and front **/
    typedef std::list<EventHandler> EventHandlerList;
    /** An event dispatcher has a handler & an virtual `on` method.
     * By default the on routine will call it's handler if it has one
     * and return the result of it's handler.
     * Otherwise it's on routine will just return false.
     *
     * Specialized EventDispatchers have overridden`on` methods.
     * These `on` methods check the event for certain conditions;
     * and then call specialized dispatchers if those conditions
     * are met.
     **/
    class EventDispatch {
      public:
        EventHandlerList handlers;
        EventDispatch();
        EventDispatch(EventHandler handler);
        EventDispatch(EventHandlerList handlers);

        virtual ~EventDispatch();
        virtual int trigger(const SDL_Event &e);
        virtual void on(EventHandler handler);

        EventDispatch(const EventDispatch &other);
        EventDispatch(EventDispatch &&other);
        EventDispatch& operator=(const EventDispatch &other);
        EventDispatch& operator=(EventDispatch &&other);

    };
    namespace events {

      class AudioDevice : public EventDispatch {
        public:
          EventDispatch added;
          EventDispatch removed;
          virtual int trigger(const SDL_Event &e) override;

      };
      class RenderReset : public EventDispatch {
        public:
          EventDispatch target;
          EventDispatch device;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Drop : public EventDispatch {
        public:
          EventDispatch file;
          EventDispatch text;
          EventDispatch begin;
          EventDispatch complete;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Finger : public EventDispatch {
        public:
          EventDispatch motion;
          EventDispatch up;
          EventDispatch down;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Mouse : public EventDispatch {
        public:
          EventDispatch motion;
          EventDispatch buttonDown;
          EventDispatch buttonUp;
          EventDispatch wheel;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Text : public EventDispatch {
        public:
          EventDispatch input;
          EventDispatch editing;
          virtual int trigger(const SDL_Event &e) override;
      };

      class Gesture : public EventDispatch {
        public:
          EventDispatch gesture;
          EventDispatch record;
          EventDispatch multigesture;
          virtual int trigger(const SDL_Event &e) override;

      };
      class Controller : public EventDispatch {
        public:
          EventDispatch axisMotion;
          EventDispatch buttonDown;
          EventDispatch buttonUp;
          EventDispatch deviceAdded;
          EventDispatch deviceRemoved;
          EventDispatch deviceRemapped;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Joystick : public EventDispatch {
        public:
          EventDispatch axisMotion;
          EventDispatch ballMotion;
          EventDispatch hatMotion;
          EventDispatch buttonUp;
          EventDispatch buttonDown;
          EventDispatch deviceAdded;
          EventDispatch deviceRemoved;
          virtual int trigger(const SDL_Event &e) override;
      };

      class App : public EventDispatch {
        public:
          EventDispatch terminating;
          EventDispatch lowMemory;
          EventDispatch willEnterBackground;
          EventDispatch didEnterBackground;
          EventDispatch willEnterForeground;
          EventDispatch didEnterForeground;
          virtual int trigger(const SDL_Event &e) override;
      };
      class KeyboardRepeats : public EventDispatch {
        public:
          EventDispatch noRepeats;
          EventDispatch onlyRepeats;
          virtual int trigger(const SDL_Event&e)override;
      };
      class Keyboard : public KeyboardRepeats {
        public:
          KeyboardRepeats down;
          KeyboardRepeats up;
          EventDispatch mapChanged;
          virtual int trigger(const SDL_Event &e) override;
      };
      class Window: public EventDispatch{
        public:
          EventDispatch shown;
          EventDispatch hidden;
          EventDispatch exposed;
          EventDispatch moved;
          EventDispatch resized;
          EventDispatch sizeChanged;
          EventDispatch minimized;
          EventDispatch maximized;
          EventDispatch restored;
          EventDispatch enter;
          EventDispatch leave;
          EventDispatch focusGained;
          EventDispatch focusLost;
          EventDispatch close;
          virtual int trigger(const SDL_Event&e) override;
      };
      class ProgramHandler : public EventDispatch {
        public:
          App app;
          AudioDevice audioDevice;
          Controller controller;
          Drop drop;
          Finger finger;
          Gesture gestures;
          Joystick joystick;
          Keyboard keyboard;
          Mouse mouse;
          RenderReset renderReset;
          Text text;
          EventDispatch user;
          EventDispatch quit;
          Window window;
          EventDispatch sysWM;
          EventDispatch clipboardUpdate;
          virtual int trigger(const SDL_Event &e) override;
      };
    }
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_EVENTDISPATCH_HPP_ */
