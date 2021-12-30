#include <iostream>
#include "game.hpp"
#include "SDL.h"

Game::Game(std::size_t grid_w, std::size_t grid_h) : snake(std::make_shared<Snake>(grid_w, grid_h)), engine(dev()), random_w(0, static_cast<int>(grid_w - 1)), random_h(0, static_cast<int>(grid_h - 1)), random_f(0, 3)
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

    if(snake->getReset())
    {
      score = 0;
      snake->resetSnake();
      // std::cout << "Snake size " << snake->getSize() << "\n";
      snake->setReset(false);
    }

    //Renders the different screens according to the state of the snake
    if(snake->getAlive()) //If the snake is alive
    {
      renderer.Render(snake, food);
    } else {
      renderer.Render();
    }

    // std::cout << "Snake size " << snake->getSize() << "\n";

    frame_end = SDL_GetTicks();

    //Keeps track of how long each loop takes
    frame_count++;
    frame_duration = frame_end - frame_start;

    //Updates the window title after every second (1000 milliseconds)
    if(frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count, snake->getLives());
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
  int x, y, f;

  while(true)
  {
    x = random_w(engine);
    y = random_h(engine);
    f = random_f(engine);

    //Checks that the location is not occupied by the Snake
    if(!snake->SnakeCell(x, y))
    {
      food.position.x = x;
      food.position.y = y;
      food.type = f;
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
  if(food.position.x == new_x && food.position.y == new_y)
  {
    switch (food.type) {
      case 0: //Good food! Snakes grows and speed goes up
        score++;
        snake->GrowBody();
        snake->setSpeed(0.01);
        break;

      case 1: //Good food! Snake gains one extra live, up to four
        snake->gainsLive();
        break;

      case 2: //Bad food :( Snake slows down and loses points(body parts)
        if(score >= 1)
        {
          score--;
          snake->shrinkSnake();
          snake->setSpeed(-0.01);
        } else {
          snake->losesLive();
        }
        break;

      case 3: //Bad food :( Snake loses a live
        snake->losesLive();
        break;

      default:
        score++;
        snake->GrowBody();
        snake->setSpeed(0.01);
        break;
    }
    PlaceFood(); //New food
  }
}
