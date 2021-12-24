#include <iostream>
#include <string>
#include "renderer.hpp"

//Overloaded constructor
Renderer::Renderer(const std::size_t screen_w, const std::size_t screen_h, const std::size_t grid_w, const std::size_t grid_h) : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer), m_screen_w(screen_w), m_screen_h(screen_h), m_grid_w(grid_w), m_grid_h(grid_h)
{
  //Initiliases SDL2
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::lock_guard<std::mutex> lock(m_mtx);
    std::cerr << "SDL could not initialise\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Creates a window
  m_window.reset(SDL_CreateWindow("Snake Game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_w, m_screen_h, SDL_WINDOW_SHOWN));
  if(m_window)
  {
    std::lock_guard<std::mutex> lock(m_mtx);
    std::cerr << "Window could not be created\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Creates renderer
  m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
  if(m_renderer)
  {
    std::lock_guard<std::mutex> lock(m_mtx);
    std::cerr << "Renderer could not be created\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

//Destroyer
Renderer::~Renderer() { }

//Renders the snake and the food in the screen
void Renderer::Render(const Snake snake, const SDL_Point &food)
{
  SDL_Rect block;
  block.w = m_screen_w / m_grid_w;
  block.h = m_screen_h / m_grid_h;

  //Clears the screen
  SDL_SetRenderDrawColor(m_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(m_renderer.get());

  //Renders food in the screen
  SDL_SetRenderDrawColor(m_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(m_renderer.get(), &block);

  //Renders the Snake's body
  SDL_SetRenderDrawColor(m_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(m_renderer.get(), &block);
  }

  //Render Snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if(snake.getAlive())
  {
    SDL_SetRenderDrawColor(m_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(m_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(m_renderer.get(), &block);

  //Updates the screen
  SDL_RenderPresent(m_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(m_window.get(), title.c_str());
}
