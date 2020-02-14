/*
 * Log.hpp
 *
 *  Created on: Feb 6, 2020
 *      Author: badquanta
 */

#ifndef SDL2_LOG_HPP_
#define SDL2_LOG_HPP_
#include <string_view>
#include <SDL2/SDL.h>

#include <stdarg.h>
namespace bq {
  namespace sdl2 {

    class Log {
      public:
        int category;
        static Log Application;
        static Log Error;
        static Log Assert;
        static Log System;
        static Log Audio;
        static Log Video;
        static Log Render;
        static Log Input;
        static Log Test;
        static Log Custom;
        Log(int category);
        virtual ~Log();
        Log(const Log &other);
        Log(Log &&other);
        Log& operator=(const Log &other);
        Log& operator=(Log &&other);

        void setPriority(SDL_LogPriority p);
        SDL_LogPriority getPriority();
        static void allPriority(SDL_LogPriority p);
        static void messageV(int cat, SDL_LogPriority pri, const std::string_view&str, va_list arg);
        static void message(int cat, SDL_LogPriority pri, const std::string_view&str, ...);
        static void log(const std::string_view& fmt,...);
        void operator()(const std::string_view& fmt,...);
        static void critical(int cat, const std::string_view& fmt,...);
        static void debug(int cat, const std::string_view& fmt,...);
        static void error(int cat, const std::string_view& fmt,...);
        static void info(int cat, const std::string_view& fmt,...);
        static void warn(int cat, const std::string_view& fmt,...);
        static void verbose(int cat, const std::string_view& fmt,...);
        void messageV(SDL_LogPriority pri, const std::string_view&str, va_list arg);
        void message(SDL_LogPriority pri, const std::string_view&str, ...);
        void critical(const std::string_view& fmt,...);
        void debug(const std::string_view& fmt,...);
        void error(const std::string_view& fmt,...);
        void info(const std::string_view& fmt,...);
        void verbose(const std::string_view& fmt,...);
        void warn(const std::string_view& fmt,...);
        static void errorSDL(int cat, const std::string_view& where);
        static void errorTTF(int cat, const std::string_view& where);
        static void errorMIX(int cat, const std::string_view&where);
        void errorMIX(const std::string_view&where);
        void errorSDL(const std::string_view& explain);
        void errorTTF(const std::string_view& explain);

    };

  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_LOG_HPP_ */
