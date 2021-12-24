#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cmath>
#include <mutex>
#include <vector>
#include "SDL.h"

class Snake
{
public:
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  //Constructors && Destructors
  Snake(int grid_width, int grid_height) : m_grid_width(grid_width), m_grid_height(grid_height), head_x(grid_width/2), head_y(grid_height/2) { }

  //Getters && Setters
  void setAlive(bool status) { m_alive = status; }
  bool getAlive() const { return m_alive; }

  //Behaviour methods
  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  void Collision();

  //Variables
  float head_x;
  float head_y;
  Direction direction = Direction::kUp;
  float speed{0.1f};
  int size{1};
  std::vector<SDL_Point> body; //SDL_Point is a struct with int x and int y coordinates

private:
  //Bheaviour methods
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  //Variables
  int m_grid_width;
  int m_grid_height;
  bool m_growing{false};
  bool m_alive{true};
};

#endif
