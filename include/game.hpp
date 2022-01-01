#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

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
  void SaveScore(int score);
  void LoadScores();

  //Getters && Setters
  int GetScore() const { return score; }
  int GetSize() const { return snake->getSize(); }

private:
  std::shared_ptr<Snake> snake;
  Foods m_foods;

  int score{0};
  std::vector <std::pair <std::string, int> > high_scores;

  //Typical behaviour methods
  void PlaceFood();
  void Update();
};

#endif /*   game.hpp    */
