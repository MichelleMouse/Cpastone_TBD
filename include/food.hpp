#ifndef FOOD_HPP
#define FOOD_HPP

#include <memory>
#include <random>
#include <unordered_map>
#include <vector>
#include "SDL.h"

class Food
{
public:
  Food(SDL_Colour colour, int type);
  void reset();

  //Getters && Setters
  int getType() { return m_type; }
  bool getState() { return m_state; }
  SDL_Colour getColour() { return m_colour; }
  SDL_Point getPosition() { return m_position; }
  void setPosition(SDL_Point pos) { m_position = pos; }
  void setState(bool state) { m_state = state; }

  //Typical behaviour methods


private:
  SDL_Colour m_colour;
  SDL_Point m_position;
  int m_type;
  bool m_state{false};
};

class Foods
{
public:
  Foods();

  //Getters && Setters
  SDL_Colour getColour() const;
  int getType() const;
  SDL_Point getPosition() const;

  //Typical behavour methods
  int impact(int const &x, int const &y);
  void placeFood(int const &x, int const &y);

private:
  std::vector< std::shared_ptr<Food> > m_food;
  int m_active_food;    //Which element in the m_food vector is being called
  //Random Number Generator
  std::random_device m_dev;                         //Used as a seed to feed mt19937
  std::mt19937 m_engine;                            //Mersenne Twister Engine
  std::uniform_int_distribution<int> m_random_w;    //0 to the grid width - 1
  std::uniform_int_distribution<int> m_random_h;    //0 to the grid height - 1
  std::uniform_int_distribution<int> m_random_f;    //0 to 3 for the type of food
};

//Struct for the snake's food
// struct Foods
// {
//   SDL_Point position;
//   int type;
//   std::vector<SDL_Colour> colours {
//     {0x79, 0xD6, 0x00},   //#79d600 Good food! Snake grows and speed goes up
//     {0x00, 0x96, 0xD6},   //#0096d6 Good food! Extra live, for a maximum of 4
//     {0xD6, 0x6F, 0x00},   //#d66f00 Bad food! Snake slows down and loses 1 point(body part)
//     {0xD6, 0x00, 0x6F}    //#d6006f Bad food! Snake loses a live
//   };
// };

#endif /*   food.hpp    */
