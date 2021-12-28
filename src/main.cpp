#include <iostream>
#include <mutex>
#include "controller.hpp"
#include "game.hpp"
#include "renderer.hpp"

std::mutex g_mtx;

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};                        //In pixels
  constexpr std::size_t kScreenHeight{640};                       //In pixels
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);

  //Prints score and size once the game is over
  std::lock_guard<std::mutex> mLock(g_mtx);
  std::cout << "Thanks for playin, come back soon :D\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  return 0;
}
