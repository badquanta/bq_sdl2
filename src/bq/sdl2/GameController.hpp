/*
 * GameController.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: badquanta
 */

#ifndef SDL2_GAMECONTROLLER_HPP_
#define SDL2_GAMECONTROLLER_HPP_

namespace bq {
  namespace sdl2 {
    
    class GameController {
      public:
        GameController();
        virtual ~GameController();
        GameController(const GameController &other);
        GameController(GameController &&other);
        GameController& operator=(const GameController &other);
        GameController& operator=(GameController &&other);
    };
  
  } /* namespace sdl2 */
} /* namespace bq */

#endif /* SDL2_GAMECONTROLLER_HPP_ */
