# Hello Raylib! A Breakout Saga
Welcome to this chill little Breakout game built with raylib. It's a simple and fun brick-breaking game where you control the paddle, bounce the ball, and break all those colorful bricks to score points!

## How to Play

- Use the **left** and **right arrow keys** to move your paddle.
- Hit the **spacebar** to launch the ball.
- Bounce the ball off your paddle to break all the bricks above.
- Try to clear all the bricks without letting the ball fall off the screen.
- If you break all the bricks, you win — if you miss the ball, it's game over.
- Press **spacebar** to restart anytime.

## Features

- Smooth gameplay with easy controls
- Multiple rows of bricks with different colors
- Score system to keep track of your progress
- Sounds for hitting bricks, winning, and losing
- Simple and clean visuals for a relaxed gaming vibe
- FPS display so you can see the performance in real time

## Tech Stuff

- Made using raylib for graphics and audio
- Written in C/C++
- Uses structs for easy game state management
- Collision detection for ball, paddle, and bricks
- Sound effects included to make it more engaging
- Built with **CMake** so it should build anywhere easily on your platform

## Building and Running

To generate build files in separate directory and build the project, use these commands:
```bash
cmake -B build && cmake --build build
```
Then to run the game:
```bash
cd build && ./breakout
```

Don't want to build it yourself? It's available here https://dietcokechan.itch.io/breakout

Easy peasy! Ready to have some fun smashing those bricks?

Feel free to tweak it, add new features, or just chill and enjoy the game. If you do, let me know — always love to hear about your mods or improvements!

Enjoy your game time and keep it chill!
