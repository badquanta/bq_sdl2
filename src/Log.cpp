/*
 * Log.cpp
 *
 *  Created on: Feb 6, 2020
 *      Author: badquanta
 */

#include "Log.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

namespace bq {
  namespace sdl2 {
    Log Log::Application = SDL_LOG_CATEGORY_APPLICATION;
    Log Log::Error = SDL_LOG_CATEGORY_ERROR;
    Log Log::Assert = SDL_LOG_CATEGORY_ASSERT;
    Log Log::System = SDL_LOG_CATEGORY_SYSTEM;
    Log Log::Audio = SDL_LOG_CATEGORY_AUDIO;
    Log Log::Video = SDL_LOG_CATEGORY_VIDEO;
    Log Log::Render = SDL_LOG_CATEGORY_RENDER;
    Log Log::Input = SDL_LOG_CATEGORY_INPUT;
    Log Log::Test = SDL_LOG_CATEGORY_TEST;
    Log Log::Custom = SDL_LOG_CATEGORY_CUSTOM;

    Log::Log(int c)
        : category { c } {
      // TODO Auto-generated constructor stub

    }

    Log::~Log() {
      // TODO Auto-generated destructor stub
    }

    Log::Log(const Log &other) {
      // TODO Auto-generated constructor stub

    }

    Log::Log(Log &&other) {
      // TODO Auto-generated constructor stub

    }

    Log& Log::operator=(const Log &other) {
      // TODO Auto-generated method stub

    }

    Log& Log::operator=(Log &&other) {
      // TODO Auto-generated method stub

    }
    /**
     * @link https://wiki.libsdl.org/SDL_LogMessageV?highlight=%28%5CbCategoryLog%5Cb%29%7C%28CategoryEnum%29%7C%28CategoryStruct%29
     */
    void Log::messageV(int cat, SDL_LogPriority pri,
        const std::string_view &str, va_list arg) {
      SDL_LogMessageV(cat, pri, str.data(), arg);
    }
    void Log::message(int cat, SDL_LogPriority pri,
        const std::string_view &str, ...) {
      SDL_LogMessage(cat, pri, str.data(), 5);
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, pri, str.data(), args);
      va_end(args);
    }
    void Log::critical(int cat, const std::string_view &str,
        ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_CRITICAL, str.data(),
          args);
      va_end(args);
    }
    void Log::debug(int cat, const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_DEBUG, str.data(),
          args);
      va_end(args);
    }
    void Log::error(int cat, const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_ERROR, str.data(),
          args);
      va_end(args);
    }

    void Log::errorSDL(int cat, const std::string_view &where) {
      error(cat, "%s : SDL_Error(%s);", where, SDL_GetError());
    }
    void Log::errorSDL(const std::string_view &explain) {
      errorSDL(category, explain);
    }
    void Log::errorTTF(int cat, const std::string_view &where) {
      error(cat, "%s => TTF_Error(%s);", where, SDL_GetError());
    }
    void Log::errorTTF(const std::string_view &where) {
      errorTTF(category, where);
    }
    void Log::errorMIX(int cat, const std::string_view &where) {
      error(cat, "%s : %s", where, Mix_GetError());
    }
    void Log::errorMIX(const std::string_view &where) {
      errorMIX(category, where);
    }

    void Log::warn(int cat, const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_WARN, str.data(),
          args);
      va_end(args);
    }
    void Log::verbose(int cat, const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_VERBOSE, str.data(),
          args);
      va_end(args);
    }
    void Log::info(int cat, const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(cat, SDL_LOG_PRIORITY_INFO, str.data(),
          args);
      va_end(args);
    }

    void Log::log(const std::string_view &str, ...) {
      va_list a_list;
      va_start(a_list, str);
      SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
          SDL_LOG_PRIORITY_INFO, str.data(), a_list);
      va_end(a_list);
    }

    void Log::messageV(SDL_LogPriority pri,
        const std::string_view &str, va_list arg) {
      SDL_LogMessageV(category, pri, str.data(), arg);
    }
    void Log::message(SDL_LogPriority pri,
        const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, pri, str.data(), args);
      va_end(args);
    }
    void Log::critical(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_CRITICAL,
          str.data(), args);
      va_end(args);
    }
    void Log::debug(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_DEBUG,
          str.data(), args);
      va_end(args);
    }
    void Log::error(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_ERROR,
          str.data(), args);
      va_end(args);
    }
    void Log::warn(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_WARN, str.data(),
          args);
      va_end(args);
    }
    void Log::info(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_INFO, str.data(),
          args);
      va_end(args);
    }
    void Log::operator ()(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_INFO, str.data(),
          args);
      va_end(args);
    }
    void Log::verbose(const std::string_view &str, ...) {
      va_list args;
      va_start(args, str);
      SDL_LogMessageV(category, SDL_LOG_PRIORITY_VERBOSE,
          str.data(), args);
      va_end(args);
    }

    void Log::allPriority(SDL_LogPriority p) {
      SDL_LogSetAllPriority(p);
    }

    void Log::setPriority(SDL_LogPriority p) {
      SDL_LogSetPriority(category, p);
    }
    SDL_LogPriority Log::getPriority() {
      SDL_LogGetPriority(category);
    }

  } /* namespace sdl2 */
} /* namespace bq */
