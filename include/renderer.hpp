#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <utility>
#include <string>
#include <vector>
#include "food.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "snake.hpp"

//So I can create a unique_ptr of SDL_Window
struct SDLWindowDeleter
{
  void operator()(SDL_Window* w) const
  {
    SDL_DestroyWindow(w);
  }
};

//So I can create a unique_ptr of SDL_Renderer
struct SDLRendererDeleter
{
  void operator()(SDL_Renderer* r) const
  {
    SDL_DestroyRenderer(r);
  }
};

class Renderer
{
public:
  //Constructors && Destructor
  Renderer(const std::size_t screen_w, const std::size_t screen_h, const std::size_t grid_w, const std::size_t grid_h);
  ~Renderer();

  //Typical behaviour methods
  void Render();
  void Render(std::shared_ptr<Snake> const &snake, Foods const &food);
  void UpdateWindowTitle(int score, int fps, int lives, std::pair<std::string, int> high_score);

private:
  //SDL Variables
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
  std::unique_ptr<SDL_Surface> m_surface;

  typedef std::shared_ptr<SDL_Texture> SharedTexture;
  SharedTexture m_texture;

  //Variables
  const std::size_t m_screen_w;
  const std::size_t m_screen_h;
  const std::size_t m_grid_w;
  const std::size_t m_grid_h;

  //Typical behaviour methods
  inline SharedTexture make_shared(SDL_Texture* texture) { return SharedTexture(texture, SDL_DestroyTexture); }
};

#endif /*   renderer.hpp    */
