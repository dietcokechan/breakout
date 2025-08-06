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
const int brickRows = 6;
const int brickRowCount = 12;
const int brickPadding = 6;
Color colors[3] = {DARKBLUE, BLUE, SKYBLUE};
Rectangle bricks[brickRows][brickRowCount] = { 0 };
Vector2 brickSize = { 60, 30 };

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

  // init bricks
  int initialPos = 60;
  
  for (int i = 0; i < brickRows; i++) {
    int paddingX = brickSize.x / 2 + brickPadding;
    
    for (int j = 0; j < brickRowCount; j++) {
      bricks[i][j].x = j * brickSize.x + paddingX;
      bricks[i][j].y = i * brickSize.y + initialPos;
      
      paddingX += brickPadding;
    }
    initialPos += brickPadding;
  }
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
  DrawCircle(bPosX, bPosY + 100, bRadius, MAROON);

  // draw bricks
  for (int i = 0; i < brickRows; i++) {
    Color brickColor = colors[i % 3];
    for (int j = 0; j < brickRowCount; j++) {
      DrawRectangle(bricks[i][j].x - brickSize.x / 2, bricks[i][j].y - brickSize.y / 2, brickSize.x, brickSize.y, brickColor);
    }
  }
  
  DrawFPS(10, 10);
  EndDrawing();
}

int main() {
  InitWindow(screenWidth, screenHeight, "Breakout");
  SetTargetFPS(60);
  InitGame();
  
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }
  
  CloseWindow();
  
  return 0;
}
