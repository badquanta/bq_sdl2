/*
 * Joystick.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_JOYSTICK_HPP_
#define SDL2_JOYSTICK_HPP_
#include <SDL2/SDL.h>
#include <map>
#include <mutex>
#include <memory>
#include "shared_ptrs.hpp"
#include <bq/WeakPtrCache.hpp>
namespace bq {
  namespace sdl2 {

    class Joystick {
      public:
        static bool init();
        static bool wasInit();
        static WeakPtrCache<SDL_Joystick*,Joystick> get_sptr;
        Joystick(SDL_Joystick*);
        virtual ~Joystick();

        /***
         * @link https://wiki.libsdl.org/SDL_NumJoysticks?highlight=%28%5CbCategoryJoystick%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
         ***/
        static int count();
        /**
         *
         */
        /***
         *
         */
        static Joystick_sptr open(int i);
        Joystick_sptr fromInstanceId(SDL_JoystickID);
        Haptic_sptr openHaptic();
        static int eventState(int state = SDL_QUERY);
        static bool eventsEnabled();
        static bool enableEvents();
        static bool disableEvents();
        static bool ensureEvents();
        static void update();
        static std::string_view nameForIndex(int idx);
        void close();
        SDL_JoystickPowerLevel powerLevel();


        bool attached();
        Sint16 axis(int);
        SDL_Point ball(int);
        Uint8 button(int);
        static SDL_JoystickGUID deviceGUID(int);
        SDL_JoystickGUID GUID();
        static SDL_JoystickGUID GUIDFromString(std::string_view guidStr);
        static std::string GUIDString(SDL_JoystickGUID guid);
        Uint8 hat(int);
        SDL_JoystickID instanceID();
        std::string_view name();
        int axisCount();
        int ballCount();
        int buttonCount();
        int hatCount();
        Joystick(const Joystick &other)=delete;
        Joystick(Joystick &&other)=delete;
        Joystick& operator=(const Joystick &other)=delete;
        Joystick& operator=(Joystick &&other)=delete;
      protected:
        SDL_Joystick* pJoystick;

    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_JOYSTICK_HPP_ */
