#include <iostream>
#include "game.hpp"
#include "SDL.h"

Game::Game(std::size_t grid_w, std::size_t grid_h)
    : snake(std::make_shared<Snake>(grid_w, grid_h))
{
  PlaceFood();
  LoadScores();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  //Game loop Input/Update/Render
  while(running)
  {
    // std::cout << "start\n";
    frame_start = SDL_GetTicks();

    //Input, Update, Render
    controller.HandleInput(running, snake);
    // std::cout << "input\n";
    Update();

    if(snake->getReset())
    {
      score = 0;
      snake->resetSnake();
      snake->setReset(false);
      LoadScores();
    }

    //Renders the different screens according to the state of the snake
    if(snake->getAlive()) //If the snake is alive
    {
      // std::cout << "Render\n";
      renderer.Render(snake, m_foods);
    } else {
      // std::cout << "Dead snake\n";
      SaveScore(score);
      renderer.Render();
    }

    frame_end = SDL_GetTicks();

    //Keeps track of how long each loop takes
    frame_count++;
    frame_duration = frame_end - frame_start;

    //Updates the window title after every second (1000 milliseconds)
    if(frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count, snake->getLives(), high_scores[0]);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    //Delays the loop to achieve the correct frame rate
    if(frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

//Places new food for the snake
void Game::PlaceFood()
{
  m_foods.placeFood(static_cast<int>(snake->getHeadX()), static_cast<int>(snake->getHeadY()));
}

void Game::Update()
{
  if(!snake->getAlive())
  {
    return;
  }

  snake->Update();

  int new_x = static_cast<int>(snake->getHeadX());
  int new_y = static_cast<int>(snake->getHeadY());

  //Checks if the snake ate the food
  switch (m_foods.impact(new_x, new_y)) {
    case 0: //Good food! Snakes grows and speed goes up
      std::cout << "\n\n\nGood food!\n";
      score++;
      snake->GrowBody();
      snake->setSpeed(0.01);
      PlaceFood();
      break;

    case 1: //Good food! Snake gains one extra live, up to four
      std::cout << "\n\n\nExtra live!\n";
      snake->gainsLive();
      PlaceFood();
      break;

    case 2: //Bad food :( Snake slows down and loses points(body parts)
      std::cout << "\n\n\nBad food!\n";
      if(score >= 1)
      {
        score--;
        snake->shrinkSnake();
        snake->setSpeed(-0.01);
      } else {
        snake->losesLive();
      }
      PlaceFood();
      break;

    case 3: //Bad food :( Snake loses a life
      std::cout << "\n\n\nLose life!\n";
      snake->losesLive();
      PlaceFood();
      break;

    default:
      // std::cout << "No food!\n";
      break;
  }

  // PlaceFood(); //Places new food
}

//Loads the latest high scores
void Game::LoadScores()
{
  std::ifstream file("../data/high_scores.txt");
  std::string line, name;
  int score;
  if(file.is_open())
  {
    while(std::getline(file, line))
    {
      std::istringstream linestream(line);
      while(linestream >> name >> score)
      {
        high_scores.emplace_back(std::make_pair(name, score));
      }
    }
    file.close();
  }
}

void Game::SaveScore(int score)
{
  //Goes though the highscores starting from the lowest
  for(int i = high_scores.size() - 1; i >= 0; --i)
  {
    //Checks if the score is higher than the saved high scores
    if(score >= high_scores[i].second && score < high_scores[i-1].second)
    {
      // std::cout << "New highscore achieved! Congratulations AAA\n";
      auto pos = high_scores.begin() + i;
      high_scores.insert(pos, std::make_pair("AAA", score));
      high_scores.pop_back();

      //Saves the new vector in the file and returns
      std::ofstream file("../data/high_scores.txt");
      if(file.is_open())
      {
        for(std::pair<std::string, int> &value : high_scores)
        {
          file << value.first << " " << value.second << "\n";
        }
        file.close();
      }
      return;
    }
  }
}
