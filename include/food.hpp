#ifndef FOOD_HPP
#define FOOD_HPP

#include <unordered_map>
#include <vector>
#include "SDL.h"

//Struct for the snake's food
struct Foods
{
  SDL_Point position;
  int type;
  std::vector<SDL_Colour> colours {
    {0x79, 0xD6, 0x00},   //#79d600 Good food! Snake grows and speed goes up
    {0x00, 0x96, 0xD6},   //#0096d6 Good food! Extra live, for a maximum of 4
    {0xD6, 0x6F, 0x00},   //#d66f00 Bad food! Snake slows down and loses 1 point(body part)
    {0xD6, 0x00, 0x6F}    //#d6006f Bad food! Snake loses a live
  };
};

#endif /*   food.hpp    */
