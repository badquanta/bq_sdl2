/*
 * Joystick.cpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#include "Joystick.hpp"

#include "Subsystem.hpp"
#include "Log.hpp"
#include "Haptic.hpp"
namespace bq {
  namespace sdl2 {
    WeakPtrCache<SDL_Joystick*, Joystick> Joystick::get_sptr(stdOnCacheMissKey<SDL_Joystick*,Joystick>);
    Haptic_sptr Joystick::openHaptic(){
      if(pJoystick&&haptic::init()){
        SDL_Haptic* sdl_haptic = SDL_HapticOpenFromJoystick(pJoystick);
        if(sdl_haptic){
          return Haptic::get_sptr(sdl_haptic);
        }
      }
      return nullptr;
    }
    bool Joystick::init() {
      return wasInit() || sdl2::init(SDL_INIT_JOYSTICK);
    }
    bool Joystick::wasInit() {
      return sdl2::wasInit(SDL_INIT_JOYSTICK);
    }
    int Joystick::count() {
      if(!init())return 0;
      int num = SDL_NumJoysticks();
      if (num < 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return num;
    }
    Joystick_sptr Joystick::open(int i) {
      static std::map<int, std::weak_ptr<Joystick>> cache;
      static std::mutex m;
      std::lock_guard<std::mutex> hold(m);
      auto sp = cache[i].lock();
      if (!sp&&init()) {
        SDL_Joystick *sdl_joystick = SDL_JoystickOpen(i);
        if (!sdl_joystick) {
          Log::Input.errorSDL(__PRETTY_FUNCTION__);
        } else {
          cache[i] = sp = get_sptr(sdl_joystick);
        }
      }
      return sp;
    }
    Joystick_sptr Joystick::fromInstanceId(SDL_JoystickID id) {
      static std::map<SDL_JoystickID, std::weak_ptr<Joystick>> cache;
      static std::mutex m;
      std::lock_guard<std::mutex> hold(m);
      auto sp = cache[id].lock();
      if (!sp) {
        SDL_Joystick *sdl_joystick = SDL_JoystickFromInstanceID(id);
        if (!sdl_joystick) {
          Log::Input.errorSDL(__PRETTY_FUNCTION__);
        } else {
          cache[id] = sp = get_sptr(sdl_joystick);
        }
      }
      return sp;
    }

    int Joystick::eventState(int state) {
      return SDL_JoystickEventState(state);
    }

    bool Joystick::eventsEnabled() {
      return (eventState() == 1);
    }

    bool Joystick::enableEvents() {
      return (eventState(SDL_ENABLE) == 1);
    }

    bool Joystick::disableEvents() {
      return (eventState(SDL_IGNORE) == 0);
    }

    bool Joystick::ensureEvents() {
      return (eventsEnabled() || enableEvents());
    }

    void Joystick::update() {
      SDL_JoystickUpdate();
    }

    std::string_view Joystick::nameForIndex(int idx) {
      const char *name = SDL_JoystickNameForIndex(idx);
      if (!name) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return name;
    }

    std::string_view Joystick::name() {
      const char *name = SDL_JoystickName(pJoystick);
      if (!name) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return name;
    }

    std::string Joystick::GUIDString(SDL_JoystickGUID guid) {
      static const int cbGUID = 64; //TODO: docs say "at least" 33 bytes; so roughly double.
      static char buffer[cbGUID];
      SDL_JoystickGetGUIDString(guid, &buffer[0], cbGUID);
      return buffer;
    }

    SDL_JoystickGUID Joystick::GUIDFromString(
        std::string_view guidStr) {
      return SDL_JoystickGetGUIDFromString(guidStr.data());
    }

    SDL_JoystickGUID Joystick::deviceGUID(int idx) {
      return SDL_JoystickGetDeviceGUID(idx);
    }

    SDL_JoystickGUID Joystick::GUID() {
      return SDL_JoystickGetGUID(pJoystick);
    }

    SDL_JoystickID Joystick::instanceID() {
      return SDL_JoystickInstanceID(pJoystick);
    }

    Uint8 Joystick::hat(int h) {
      return SDL_JoystickGetHat(pJoystick, h);
    }
    SDL_JoystickPowerLevel Joystick::powerLevel(){
      SDL_JoystickPowerLevel l = SDL_JoystickCurrentPowerLevel(pJoystick);
      if(l==SDL_JOYSTICK_POWER_UNKNOWN){
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return l;
    }
    int Joystick::hatCount() {
      int c = SDL_JoystickNumHats(pJoystick);
      if (c < 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return c;
    }
    int Joystick::buttonCount() {
      int c = SDL_JoystickNumButtons(pJoystick);
      if (c < 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return c;
    }
    Uint8 Joystick::button(int idx) {
      return SDL_JoystickGetButton(pJoystick, idx);
    }
    int Joystick::ballCount() {
      int c = SDL_JoystickNumBalls(pJoystick);
      if (c < 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return c;
    }
    SDL_Point Joystick::ball(int idx) {
      SDL_Point p;
      if (SDL_JoystickGetBall(pJoystick, idx, &p.x, &p.y) != 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return p;
    }
    int Joystick::axisCount() {
      int c = SDL_JoystickNumAxes(pJoystick);
      if (c < 0) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
      }
      return c;
    }
    Sint16 Joystick::axis(int idx) {
      return SDL_JoystickGetAxis(pJoystick, idx);
    }

    bool Joystick::attached() {
      if (SDL_JoystickGetAttached(pJoystick) != SDL_TRUE) {
        Log::Input.errorSDL(__PRETTY_FUNCTION__);
        return false;
      }
      return true;
    }

    Joystick::Joystick(SDL_Joystick *j)
        : pJoystick(j) {
      Log::Input.info(__PRETTY_FUNCTION__);

    }

    Joystick::~Joystick() {
      Log::Input.info(__PRETTY_FUNCTION__);
    }
  /**
   iJoystick::iJoystick(const iJoystick &other) {
   // TODO Auto-generated constructor stub

   }

   iJoystick::iJoystick(iJoystick &&other) {
   // TODO Auto-generated constructor stub

   }

   iJoystick& iJoystick::operator=(const iJoystick &other) {
   // TODO Auto-generated method stub

   }

   iJoystick& iJoystick::operator=(iJoystick &&other) {
   // TODO Auto-generated method stub

   }
   **/
  } /* namespace sdl2 */
} /* namespace bq */
