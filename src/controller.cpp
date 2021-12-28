#include <iostream>
#include "controller.hpp"
#include "SDL.h"
#include "snake.hpp"

Controller::Controller(std::size_t screen_w, std::size_t screen_h, std::size_t grid_w, std::size_t grid_h) : m_screen_w(screen_w), m_screen_h(screen_h), m_grid_w(grid_w), m_grid_h(grid_h) { }

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
      //Unloads the dynamically loaded image libraries
      IMG_Quit();
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
      //Replays the game when the snake is dead and the button is clicked
      if(!snake->getAlive())
      {
        if((e.button.x >= ((m_screen_w / 2) - (m_screen_w / 4))) && (e.button.x <= ((m_screen_w / 2) + (m_screen_w / 4))))
        {
          if((e.button.y >= ((m_screen_h / 2) - (m_screen_h / 16))) && (e.button.y <= ((m_screen_h / 2) + (m_screen_h / 16))))
          {
            snake->setReset(true);
          }
        }
      }
    }
  }
}
