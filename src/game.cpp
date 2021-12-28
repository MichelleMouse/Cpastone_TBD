#include <iostream>
#include "game.hpp"
#include "SDL.h"

Game::Game(std::size_t grid_w, std::size_t grid_h) : snake(std::make_shared<Snake>(grid_w, grid_h)), engine(dev()), random_w(0, static_cast<int>(grid_w - 1)), random_h(0, static_cast<int>(grid_h - 1))
{
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  //Game loop Input/Update/Render
  while(running)
  {
    frame_start = SDL_GetTicks();

    //Input, Update, Render
    controller.HandleInput(running, snake);
    Update();

    //Renders the different screens according to the state of the snake
    if(snake->getAlive()) //If the snake is alive
    {
      renderer.Render(snake, food);
    } else {
      renderer.Render();
    }

    frame_end = SDL_GetTicks();

    //Keeps track of how long each loop takes
    frame_count++;
    frame_duration = frame_end - frame_start;

    //Updates the window title after every second (1000 milliseconds)
    if(frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    //Delays the loop to achieve the correct frame rate
    if(frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;

  while(true)
  {
    x = random_w(engine);
    y = random_h(engine);

    //Checks that the location is not occupied by the Snake
    if(!snake->SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if(!snake->getAlive())
  {
    return;
  }

  snake->Update();

  int new_x = static_cast<int>(snake->getHeadX());
  int new_y = static_cast<int>(snake->getHeadY());

  //Checks if the snake ate the food
  if(food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood(); //New food
    //Grows the snake and increases the speed
    snake->GrowBody();
    snake->setSpeed(0.01);
  }
}
