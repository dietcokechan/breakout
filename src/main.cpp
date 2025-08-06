#include "raylib.h"

#define screenWidth 800
#define screenHeight 600

// constant variables
static const int pWidth = 160;
static const int pHeight = 20;
static const int bRadius = 16;

// global variables
int pRectX, pRectY;
int bPosX, bPosY;
int direction;
float speed;

// functions
static void InitGame();
static void UpdateGame();
static void DrawGame();

// initialization
void InitGame() {
  // init player
  pRectX = (screenWidth - pWidth) / 2;
  pRectY = (screenHeight - pHeight) / 2;

  // init ball
  bPosX = (screenWidth - bRadius) / 2;
  bPosY = (screenHeight - bRadius) / 2;

  // idle ball anim
  direction = 1;
  speed = 5.0f;

  InitWindow(screenWidth, screenHeight, "Breakout");
  
  SetTargetFPS(60);
}

// update
void UpdateGame() {
  // move ball side to side
  bPosX += direction * speed;
  if (bPosX + bRadius >= screenWidth || bPosX - bRadius <= 0) {
    direction *= -1;
  }

  // player input
  if (IsKeyDown(KEY_RIGHT)) pRectX += 5.0f;
  if (IsKeyDown(KEY_LEFT)) pRectX -= 5.0f;
}

// drawing
void DrawGame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  
  // draw player rect
  DrawRectangle(pRectX, pRectY + 200, pWidth, pHeight, BLACK);

  // draw ball
  DrawCircle(bPosX, bPosY + 100, bRadius, RED); 
  
  DrawFPS(10, 10);
  
  EndDrawing();
}

int main() {
  InitGame();

  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }
  
  CloseWindow();
  
  return 0;
}
