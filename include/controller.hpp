#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "snake.hpp"

class Controller
{
public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const;


private:
  void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif /*   controller.hpp    */
