#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <memory>
#include "SDL_image.h"
#include "snake.hpp"

class Controller
{
public:
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const;
  Controller(std::size_t screen_w, std::size_t screen_h, std::size_t grid_w, std::size_t grid_h);

private:
  //Variables
  std::size_t m_screen_w;
  std::size_t m_screen_h;
  std::size_t m_grid_w;
  std::size_t m_grid_h;

  //Typical behaviour methods
  void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif /*   controller.hpp    */
