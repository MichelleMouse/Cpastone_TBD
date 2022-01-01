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

void Food::reset()
{
  m_state = false;
  m_position = {-1, -1};
}

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
    // std::cout << "\n\n\nNew position x: " << m_food[m_active_food]->getPosition().x << " y: " << m_food[m_active_food]->getPosition().y << "\n";
    // std::cout << "\n\n\nNew type: " << m_food[m_active_food]->getType() << "\n";
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
      std::cout << "Type of impact: " << f->getType() << "\n";
      f->reset();
      return f->getType();
    }
  }

  return -1;
}

void Foods::placeFood(int const &x, int const &y)
{
  int fX, fY, fT;

  // while(true)
  // {
    fX = m_random_w(m_engine);
    fY = m_random_h(m_engine);
    m_active_food = m_random_f(m_engine);

    if(fX != x && fY != y && !m_food[m_active_food]->getState())
    {
      std::cout << "\n\n\n\n\nx " << fX << " y " << fY << " T " << m_active_food << "\n";
      m_food[m_active_food]->setPosition({fX, fY});
      m_food[m_active_food]->setState(true);
    }
  // }
}
