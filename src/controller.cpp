#include <iostream>
#include "controller.hpp"
#include "SDL.h"
#include "snake.hpp"

void Controller::ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input, Snake::Direction opposite) const
{
  if(snake->direction != opposite || snake->getSize() == 1)
  {
    snake->direction = input;
  }
  return;
}

void Controller::HandleInput(bool &running, std::shared_ptr<Snake> &snake) const
{
  SDL_Event e;

  while(SDL_PollEvent(&e))
  {
    if(e.type == SDL_QUIT)
    {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch(e.key.keysym.sym)
      {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      std::cout << "X " << e.button.x << " and Y " << e.button.y << "\n";
    }
  }
}
