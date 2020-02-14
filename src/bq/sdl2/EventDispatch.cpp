/*
 * Events.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */
#include "EventDispatch.hpp"
/**
 * Maro used to generate the common switch header.
 */
#define SWITCH_E_TYPE(e) \
  switch (e)
/**
 * Macro used to generate the common cases
 */
#define CASE_OF(a, b) \
  case a:\
  counts+=b.trigger(e);\
  break;

/**
 * Macro used to generate the default cases (debug log)
 */
#define CASE_DEFAULT(msg)\
  default:\
    log.debug(msg);
/**
 * Macro used to start the common on method switches.
 */
#define START_TRIGGER_SDL_EVENT_SWITCH_METHOD2(klass, eTarget) \
  int klass::trigger(const SDL_Event &e){\
    int counts = 0;\
    SWITCH_E_TYPE(e.eTarget) {

#define START_TRIGGER_SDL_EVENT_SWITCH_METHOD(klass) \
  START_TRIGGER_SDL_EVENT_SWITCH_METHOD2(klass, type)

/**
 * Macro used to end the common on method switches.
 */
#define END_ON_SDL_EVENT_SWITCH_METHOD2(failMsg,superKlass) \
    CASE_DEFAULT(failMsg)\
    }\
    counts += superKlass::trigger(e);\
    log.debug("%s counts=%d",__PRETTY_FUNCTION__,counts);\
    return counts;\
  }
#define END_ON_SDL_EVENT_SWITCH_METHOD(failMsg) \
    END_ON_SDL_EVENT_SWITCH_METHOD2(failMsg,EventDispatch)
////////////////////////////////////////////////////////
#include "Log.hpp"

/** @TODO: bq::sdl2::EventDispatch implementation documentation **/
namespace bq {
  /** @TODO: sdl2::EventDispatch implementation documentation.   **/
  namespace sdl2 {
    static Log&log=Log::System;
    /** @TODO: sdl2::event namespace implementation documentation. **/
    namespace event {
      /** TODO: document me. **/
      void pump(void){
        SDL_PumpEvents();
      }
      /** TODO: document me. **/
      Uint32 declare(int num){
        return SDL_RegisterEvents(num);
      }
      /** TODO: document me. **/
      bool push(SDL_Event*e){
        int val = SDL_PushEvent(e);
        if((val)==-1){
          log.errorSDL(__PRETTY_FUNCTION__);
        }
        return val;
      }
      /** @TODO: document me. **/
      bool wait(SDL_Event*e){
        if(SDL_WaitEvent(e)==0){
          log.errorSDL(__PRETTY_FUNCTION__);
          return false;
        }
        return true;
      }
      /** @TODO: document me. **/
      bool waitTimeout(SDL_Event*e,int timeout){
        if(SDL_WaitEventTimeout(e,timeout)==0){
          log.errorSDL(__PRETTY_FUNCTION__);
          return false;
        }
        return true;
      }
      /** @TODO: document me. **/
      bool hasAny(Uint32 minType, Uint32 maxType){
        return SDL_HasEvents(minType,maxType)==SDL_TRUE;
      }
      /** @TODO: document me. **/
      bool has(Uint32 type){
        return SDL_HasEvent(type)==SDL_TRUE;
      }
      /** @TODO: document me. **/
      bool enabled(Uint32 type){
        return SDL_GetEventState(type) == SDL_ENABLE;
      }
      /** @TODO: document me. **/
      bool enable(Uint32 type){
        return SDL_EventState(type,SDL_ENABLE)==SDL_ENABLE;
      }
      /** @TODO: document me. **/
      bool disable(Uint32 type){
        return SDL_EventState(type,SDL_IGNORE)==SDL_IGNORE;
      }
    }
    /**
     * poll an sdl event
     */
    bool pollEvent(SDL_Event *e) {
      return (SDL_PollEvent(e) == 1);
    }
    /**            @TODO: document me.
     */
    int EventDispatch::trigger(const SDL_Event &e) {
      int counts = 0;
      if (handlers.size() > 0) {
        for (EventHandlerList::iterator it = handlers.begin();
            it != handlers.end(); ++it) {
          if ((*it)(e)) counts++;
        }
        log.info("%s : counts = %d",__PRETTY_FUNCTION__,counts);
      }
      return counts;
    }
    /** @TODO: document me. **/
    void EventDispatch::on(EventHandler handler) {
      log.info(__PRETTY_FUNCTION__);
      handlers.push_back(handler);
    }
    /** @TODO: document me. **/
    namespace events {
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(AudioDevice)
        CASE_OF(SDL_AUDIODEVICEADDED, added)
        CASE_OF(SDL_AUDIODEVICEREMOVED, removed)
        END_ON_SDL_EVENT_SWITCH_METHOD(
            "not an audio device event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(RenderReset)
        CASE_OF(SDL_RENDER_DEVICE_RESET, device)
        CASE_OF(SDL_RENDER_TARGETS_RESET, device)
        END_ON_SDL_EVENT_SWITCH_METHOD("not a render reset event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Drop)
        CASE_OF(SDL_DROPBEGIN, begin)
        CASE_OF(SDL_DROPCOMPLETE, complete)
        CASE_OF(SDL_DROPFILE, file)
        CASE_OF(SDL_DROPTEXT, text)
        END_ON_SDL_EVENT_SWITCH_METHOD("Not a drop event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Finger)
        CASE_OF(SDL_FINGERDOWN, down)
        CASE_OF(SDL_FINGERUP, up)
        CASE_OF(SDL_FINGERMOTION, motion)
        END_ON_SDL_EVENT_SWITCH_METHOD("Not a finger event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Mouse)
        CASE_OF(SDL_MOUSEBUTTONDOWN, buttonDown)
        CASE_OF(SDL_MOUSEBUTTONUP, buttonUp)
        CASE_OF(SDL_MOUSEMOTION, motion)
        CASE_OF(SDL_MOUSEWHEEL, wheel)
        END_ON_SDL_EVENT_SWITCH_METHOD("NOT a mouse event")
      ;
      /**
       * dispatch between `down`, `up`, and `mapChaned`
       */
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Keyboard)
        CASE_OF(SDL_KEYDOWN, down)
        CASE_OF(SDL_KEYUP, up)
        CASE_OF(SDL_KEYMAPCHANGED, mapChanged)
        END_ON_SDL_EVENT_SWITCH_METHOD2("Not a key event",KeyboardRepeats)
      ;
      /** @TODO: document me. **/
      int KeyboardRepeats::trigger(const SDL_Event&e){
        int counts=0;
        if((e.type==SDL_KEYUP)||(e.type==SDL_KEYDOWN)){
          if(e.key.repeat==0){
            log.verbose("first");
            counts+=noRepeats.trigger(e);
          } else {
            counts+=onlyRepeats.trigger(e);
          }
        }
        counts+=EventDispatch::trigger(e);
        log.debug("%s counts=%d",__PRETTY_FUNCTION__,counts);
        return counts;
      }
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Text)
        CASE_OF(SDL_TEXTEDITING, editing)
        CASE_OF(SDL_TEXTINPUT, input)
        END_ON_SDL_EVENT_SWITCH_METHOD("Not a text event")
      ;

      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Gesture)
        CASE_OF(SDL_DOLLARGESTURE, gesture)
        CASE_OF(SDL_DOLLARRECORD, record)
        CASE_OF(SDL_MULTIGESTURE, multigesture)
        END_ON_SDL_EVENT_SWITCH_METHOD("not a text event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Controller)
        CASE_OF(SDL_CONTROLLERAXISMOTION, axisMotion)
        CASE_OF(SDL_CONTROLLERBUTTONDOWN, buttonDown)
        CASE_OF(SDL_CONTROLLERBUTTONUP, buttonUp)
        CASE_OF(SDL_CONTROLLERDEVICEADDED, deviceAdded)
        END_ON_SDL_EVENT_SWITCH_METHOD("not a controller event.")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(Joystick)
        CASE_OF(SDL_JOYAXISMOTION, axisMotion)
        CASE_OF(SDL_JOYBALLMOTION, ballMotion)
        CASE_OF(SDL_JOYHATMOTION, hatMotion)
        CASE_OF(SDL_JOYBUTTONDOWN, buttonDown)
        CASE_OF(SDL_JOYBUTTONUP, buttonUp)
        CASE_OF(SDL_JOYDEVICEADDED, deviceAdded)
        CASE_OF(SDL_JOYDEVICEREMOVED, deviceRemoved)
        END_ON_SDL_EVENT_SWITCH_METHOD("not a joy event")

      ;
      /** @TODO: document me. **/

      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(App)
        CASE_OF(SDL_APP_DIDENTERBACKGROUND, didEnterBackground)
        CASE_OF(SDL_APP_DIDENTERFOREGROUND, didEnterForeground)
        CASE_OF(SDL_APP_WILLENTERBACKGROUND, willEnterBackground)
        CASE_OF(SDL_APP_WILLENTERFOREGROUND, willEnterForeground)
        CASE_OF(SDL_APP_LOWMEMORY, lowMemory)
        CASE_OF(SDL_APP_TERMINATING, terminating)
        END_ON_SDL_EVENT_SWITCH_METHOD("not an app event")

      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD2(Window, window.event)
        CASE_OF(SDL_WINDOWEVENT_SHOWN, shown)
        CASE_OF(SDL_WINDOWEVENT_HIDDEN, hidden)
        CASE_OF(SDL_WINDOWEVENT_EXPOSED, exposed)
        CASE_OF(SDL_WINDOWEVENT_MOVED, moved)
        CASE_OF(SDL_WINDOWEVENT_RESIZED, resized)
        CASE_OF(SDL_WINDOWEVENT_SIZE_CHANGED, sizeChanged)
        CASE_OF(SDL_WINDOWEVENT_MINIMIZED, minimized)
        CASE_OF(SDL_WINDOWEVENT_MAXIMIZED, maximized)
        CASE_OF(SDL_WINDOWEVENT_RESTORED, restored)
        CASE_OF(SDL_WINDOWEVENT_ENTER, enter)
        CASE_OF(SDL_WINDOWEVENT_LEAVE, leave)
        CASE_OF(SDL_WINDOWEVENT_FOCUS_GAINED, focusGained)
        CASE_OF(SDL_WINDOWEVENT_FOCUS_LOST, focusLost)
        CASE_OF(SDL_WINDOWEVENT_CLOSE, close)
        END_ON_SDL_EVENT_SWITCH_METHOD("not a window event")
      ;
      /** @TODO: document me. **/
      START_TRIGGER_SDL_EVENT_SWITCH_METHOD(ProgramHandler)

        CASE_OF(SDL_QUIT, quit)

        case SDL_APP_TERMINATING:
        case SDL_APP_LOWMEMORY:
        case SDL_APP_WILLENTERBACKGROUND:
        case SDL_APP_DIDENTERBACKGROUND:
        case SDL_APP_WILLENTERFOREGROUND:
        CASE_OF(SDL_APP_DIDENTERFOREGROUND, app)
        CASE_OF(SDL_WINDOWEVENT, window)
        CASE_OF(SDL_SYSWMEVENT, sysWM)

        case SDL_KEYMAPCHANGED:
        case SDL_KEYDOWN:
        CASE_OF(SDL_KEYUP, keyboard)

        case SDL_TEXTEDITING:
        CASE_OF(SDL_TEXTINPUT, text)

        case SDL_MOUSEMOTION:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        CASE_OF(SDL_MOUSEWHEEL, mouse)

        case SDL_JOYAXISMOTION:
        case SDL_JOYBALLMOTION:
        case SDL_JOYHATMOTION:
        case SDL_JOYBUTTONDOWN:
        case SDL_JOYBUTTONUP:
        case SDL_JOYDEVICEADDED:
        CASE_OF(SDL_JOYDEVICEREMOVED, joystick)

        case SDL_CONTROLLERAXISMOTION:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERDEVICEREMAPPED:
        CASE_OF(SDL_CONTROLLERDEVICEREMOVED, controller)

        case SDL_FINGERDOWN:
        case SDL_FINGERUP:
        CASE_OF(SDL_FINGERMOTION, finger)
        case SDL_DOLLARGESTURE:
        case SDL_DOLLARRECORD:
        CASE_OF(SDL_MULTIGESTURE, gestures)
        CASE_OF(SDL_CLIPBOARDUPDATE, clipboardUpdate)
        case SDL_DROPFILE:
        case SDL_DROPTEXT:
        case SDL_DROPBEGIN:
        CASE_OF(SDL_DROPCOMPLETE, drop)
        case SDL_AUDIODEVICEADDED:
        CASE_OF(SDL_AUDIODEVICEREMOVED, audioDevice)
        case SDL_RENDER_TARGETS_RESET:
        CASE_OF(SDL_RENDER_DEVICE_RESET, renderReset)
        END_ON_SDL_EVENT_SWITCH_METHOD("Unknown e.type")
      ;
    }
    EventDispatch::EventDispatch()
        : handlers { } {
      //sdl2::log.debug("EventDispatcher constructed.");
      sdl2::log.debug(__PRETTY_FUNCTION__);
    }
    EventDispatch::~EventDispatch() {
      sdl2::log.debug("EventDispatcher destroyed.");
    }
    EventDispatch::EventDispatch(const EventDispatch &other)
        : handlers { other.handlers } {
      // TODO Auto-generated constructor stub
      sdl2::log.debug(
          "EventDispatcher constructed with copied handlers.");
    }
    EventDispatch::EventDispatch(EventDispatch &&other)
        : handlers { other.handlers } {
      sdl2::log.debug(
          "EventDispatcher constructed with copied handlers.");

    }
    EventDispatch& EventDispatch::operator=(
        const EventDispatch &other) {
      sdl2::log.debug("EventDispatcher handlers overridden.");
      handlers = other.handlers;
      return (*this);

    }
    EventDispatch& EventDispatch::operator=(
        EventDispatch &&other) {
      sdl2::log.debug("EventDispatcher handlers overridden.");
      handlers = other.handlers;
      return (*this);
    }
  } /* namespace sdl2 */
} /* namespace bq */
