#include <memory>
#include <iostream>
#include "constants.hpp"
#include "food.hpp"

/*    Food class    */
Food::Food(SDL_Colour colour, int type)
    : m_state(false)
    , m_colour(colour)
    , m_position({0,0})
    , m_type(type)
{ }

/*    Foods class     */
Foods::Foods()
    : m_engine(m_dev())
    , m_random_w(0, static_cast<int>(GRIDWIDTH - 1))
    , m_random_h(0, static_cast<int>(GRIDHEIGHT - 1))
    , m_random_f(0, 3)
{
  m_food.emplace_back(std::shared_ptr<Food>(new Food({0x79, 0xD6, 0x00}, 0))); //Good food
  m_food.emplace_back(std::shared_ptr<Food>(new Food({0x00, 0x96, 0xD6}, 1))); //Extra life
  m_food.emplace_back(std::shared_ptr<Food>(new Food({0xD6, 0x6F, 0x00}, 2))); //Bad food
  m_food.emplace_back(std::shared_ptr<Food>(new Food({0xD6, 0x00, 0x6F}, 3))); //Lose life
}

SDL_Colour Foods::getColour() const
{
  if(m_active_food != -1)
  {
    return m_food[m_active_food]->getColour();
  } else {
    return {0x1E, 0x1E, 0x1E, 0xFF};
  }
}

int Foods::getType() const
{
  if(m_active_food != -1)
  {
    return m_food[m_active_food]->getType();
  } else {
    return -1;
  }
}

SDL_Point Foods::getPosition() const
{
  if(m_active_food != -1)
  {
    return m_food[m_active_food]->getPosition();
  } else {
    return {-1, -1};
  }
}

int Foods::impact(int const &x, int const &y)
{
  for(auto f : m_food)
  {
    if(f->getState() && (x == f->getPosition().x && y == f->getPosition().y))
    {
      return f->getType();
    }
  }

  return -1;
}

void Foods::placeFood(int const &x, int const &y)
{
  int fX, fY, fT;

  fX = m_random_w(m_engine);
  fY = m_random_h(m_engine);
  fT = m_random_f(m_engine);

  // while(true)
  // {
    if(fX != x && fY != y && !m_food[fT]->getState())
    {
      m_food[fT]->setPosition({fX, fY});
      m_food[fT]->setState(true);
      m_active_food = fT;
    }
  // }
}
