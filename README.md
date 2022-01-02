# Snake_Game

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![macOS](https://svgshare.com/i/ZjP.svg)](https://svgshare.com/i/ZjP.svg) [![Atom](https://badgen.net/badge/icon/atom?icon=atom&label)](https://atom.io)

Welcome to my Capstone Project for my [Udacity's C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)!

For this project, I chose to improve the SDL game Snake inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) StackOverflow question and you can find Udacity's original repo [here](https://github.com/udacity/CppND-Capstone-Snake-Game).

I will add/have added the following features to the game:  
🐍 The snakes dies when it runs into the edges of the grid, instead of going through  
🐍 Replay button to restart the game from zero  
🐍 Save the latest 5 highest scores  
🐍 There are four different types of food that affect the snake! The bad foods timeout after a couple of seconds. The meaning of every food is as follows:  
&nbsp;&nbsp;&nbsp;&nbsp;🟢 Good food that will increase your score, the snake grows and the speed will go up  
&nbsp;&nbsp;&nbsp;&nbsp;🔵 Good food that will give you one extra live! You can gather up to 4 lives  
&nbsp;&nbsp;&nbsp;&nbsp;🟠 The snake will slow down and shrink one block. You lose 1 point from your score  
&nbsp;&nbsp;&nbsp;&nbsp;🔴 Bad food that will take one live from the snake!  

<p align="center"><img src="imgs/Game_screen.png" alt="Snake game" width="300" /><img src="imgs/Replay_screen.png" alt="Snake game" width="300" /></p>

## File and Class Structure
The folder and file structure of the project is as follows:  
📂 cmake folder where extra `.cmake` files are stored. `FindSDL2_image.cmake` file helps locate the SDL and SDL_Image libraries in the computer  
📂 imgs folder with the images for the replay screen and the readme  
📂 include folder with all the `.hpp` files  
📂 src folder with all the `.cpp` files  
📂 data folder contains the `.txt` file with the 5 highest scores in the game  

The class structure is as follows:  
🐍 A `Snake` class defined in the file `snake.hpp` and instantiated in the file `snake.cpp`. This class handles all the snake features, such as size, life status, body, head location, speed and reset.  
🎮 A `Controller` class defined in the file `controller.cpp` and instantiated in the file `controller.cpp`. This class handles all the user interactions (keys pressed and mouse events).  
🖥 A `Renderer` class defined in the file `renderer.cpp` and instantiated in the file `renderer.cpp`. This class takes care of the graphics of the game (colour of the snake, the food, creating the window, etc.).  
👾 A `Game` class defined in the file `game.cpp` and instantiated in the file `game.cpp`. This class handles the game loop (input, update, render).  

The `main.cpp` file creates objects type `Game`, `Renderer` and `Controller`, to interact with each other.

## Environment
👉 macOS 12.1 Monterey with 8-Core Intel Core i7 chip  
👉 Homebrew 3.3.5  
👉 cMake 3.21.3  
👉 GNU Make 3.81  
👉 C++ 17  
👉 Apple clang version 13.0.0  
👉 SDL 2.0.18. [Download SDL](https://www.libsdl.org/download-2.0.php) from the official website.  
👉 SDL_Image 2.0

## Compiling and Running
### SDL_Image 2
#### Ubuntu
Run the following command in the terminal
```
sudo apt-get install libsdl2-image-dev
```
#### macOS
Download the binary (`.dmg`) from [here](https://www.libsdl.org/projects/SDL_image/) and wait for it to download. Then move the `SDL2_image.framework` folder to `/Library/Frameworks/`.

If you do not have the correct permission in the computer (i.e. root or admin), read the `ReadMe.txt` inside the downloaded `.dmg`

### Compile
Create a `build` folder and change to that directory
```
mkdir build && cd build
```

Within the build directory run
```
cmake .. && make
```

### Running
The executable is within the `build` directory. You can run it as follows
```
./Snake
```

## Rubric Points
<!-- Going back to HTML because Markdown restricts format too much --->
<table>
  <tr>
    <th>Group</th>
    <th>Rubric</th>
    <th>File</th>
    <th>Line Numbers</th>
  </tr>
  <tr>
    <td rowspan="3">Loops, Functions, I/O</td>
    <td>The project demonstrates and understanding of C++ functions and control structures</td>
    <td>snake.hpp <br/> renderer.hpp</td>
    <td>8 11 <br/> 14 23 31</td>
  </tr>
  <tr>
    <td>The project reads data from a file and process the data, or the program writes data to a file</td>
    <td>game.cpp</td>
    <td>141 160</td>
  </tr>
  <tr>
    <td>The project accepts user input and process the input</td>
    <td>controller.cpp</td>
    <td>17</td>
  </tr>
  <tr>
    <td rowspan="5">Object Oriented Programming</td>
    <td>The project uses Object Oriented Programming techniques</td>
    <td>main.cpp</td>
    <td>18 19 20 21</td>
  </tr>
  <tr>
    <td>Classes use appropriate access specifiers for class members</td>
    <td>snake.hpp <br/> food.hpp <br/> controller.hpp <br/> renderer.hpp <br/> game.hpp</td>
    <td>10 46 <br> 12 26 35 47 <br/> 10 14 <br/> 33 43 <br/> 20 33 </td>
  </tr>
  <tr>
    <td>Class constructors utilise member initialisation lists</td>
    <td>controller.cpp <br/> snake.hpp <br/> food.cpp <br/> game.cpp <br/> renderer.cpp</td>
    <td>6 <br/> 21 <br/> 20 <br/> 5 <br/> 6</td>
  </tr>
  <tr>
    <td>Classes encapsulate behaviour</td>
    <td>snake.hpp <br/> food.hpp</td>
    <td>23-40 48-49 <br/> 13-22 36-45</td>
  </tr>
  <tr>
    <td>Overloaded functions allow the same function to operate on different parameters</td>
    <td>renderer.hpp</td>
    <td>39 40</td>
  </tr>
  <tr>
    <td rowspan="2">Memory Management</td>
    <td>The project makes use of references in function declarations</td>
    <td>renderer.hpp <br/> game.hpp <br/> controller.hpp <br/> food.hpp </br> snake.hpp</td>
    <td>40 <br/> 25 <br/> 11 22 </br> 44 45 </br> 49</td>
  </tr>
  <tr>
    <td>The project uses smart pointers instead of raw pointers</td>
    <td>renderer.hpp <br/> game.hpp <br/> controller.hpp <br/> food.hpp</td>
    <td>40 45 46 47 <br/> 34 <br/> 11 22 </br> 48</td>
  </tr>
</table>
