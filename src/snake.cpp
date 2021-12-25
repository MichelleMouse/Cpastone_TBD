#include <iostream>
#include "snake.hpp"

void Snake::Update()
{
  //Captures the position of the head prior to updating it
  SDL_Point prev_cell
  {
    static_cast<int>(head_x),
    static_cast<int>(head_y)
  };
  UpdateHead();
  //Captures the position of the head after updating it
  SDL_Point current_cell
  {
    static_cast<int>(head_x),
    static_cast<int>(head_y)
  };

  //If the snake's head has moved to a new cell, it updates the body vector
  if(current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }

  //If the snake's head has collided with the grid edges
  // if(current_cell.x > m_grid_width || current_cell.y > m_grid_height)
  // {
  //   std::cout << "The snake touched the border\n";
  // }
}

//Updates the head position according to the direction of the snake
void Snake::UpdateHead()
{
  switch(direction)
  {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  //Kills the snake if the head goes beyond the limits of the grid
  if(head_x > m_grid_width && head_y > m_grid_height)
  {
    m_alive = false;
  }
}

//Updates the body of the snake according to the position of the head
void Snake::UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell)
{
  //Adds the previous head location to the vector
  body.emplace_back(prev_cell);

  if(!m_growing)
  {
    body.erase(body.begin());
  } else {
    m_growing = false;
    size++;
  }

  //Checks if the snake has died
  for(auto const &item : body)
  {
    if (current_cell.x == item.x && current_cell.y == item.y)
    {
      m_alive = false;
    }
  }
}

void Snake::GrowBody()
{
  m_growing = true;
}

//Need to make efficient
bool Snake::SnakeCell(int x, int y)
{
  if(x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }

  for(auto const &item : body)
  {
    if(x == item.x && y == item.y)
    {
      return true;
    }
  }

  return false;
}

void Snake::Collision()
{

}
