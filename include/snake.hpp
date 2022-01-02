#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <cmath>
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
  Snake(int grid_width, int grid_height) : m_grid_width(grid_width), m_grid_height(grid_height), m_head_x(grid_width/2), m_head_y(grid_height/2) { }

  //Getters && Setters
  void setAlive(bool status) { m_alive = status; }
  void setSpeed(float inc) { m_speed += inc; }
  void setReset(bool reset) { m_reset = reset; }
  bool getAlive() const { return m_alive; }
  int getSize() const { return m_size; }
  float getHeadX() const { return m_head_x; }
  float getHeadY() const { return m_head_y; }
  bool getReset() const { return m_reset; }
  int getLives() const { return m_lives; }

  //Behaviour methods
  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  void resetSnake();
  void gainsLive();
  void losesLive();
  void shrinkSnake();

  //Variables
  Direction direction = Direction::kUp;
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
  bool m_reset{false};
  int m_size{1};
  int m_lives{3};
  float m_speed{0.1f};
  float m_head_x;
  float m_head_y;
};

#endif /*   snake.hpp    */
