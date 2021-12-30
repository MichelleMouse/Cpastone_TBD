#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <random>
#include "controller.hpp"
#include "food.hpp"
#include "renderer.hpp"
#include "SDL.h"
#include "snake.hpp"

class Game
{
public:
  //Constructor && Destructors
  Game(std::size_t grid_w, std::size_t grid_h);

  //Typical behaviour methods
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

  //Getters && Setters
  int GetScore() const { return score; }
  int GetSize() const { return snake->getSize(); }

private:
  std::shared_ptr<Snake> snake;
  // Snake snake;
  Foods food;

  //Random Number Generator
  std::random_device dev;                         //Used as a seed to feed mt19937
  std::mt19937 engine;                            //Mersenne Twister Engine
  std::uniform_int_distribution<int> random_w;    //0 to the grid width - 1
  std::uniform_int_distribution<int> random_h;    //0 to the grid height - 1
  std::uniform_int_distribution<int> random_f;    //0 to 3 for the type of food

  int score{0};

  //Typical behaviour methods
  void PlaceFood();
  void Update();
};

#endif /*   game.hpp    */
