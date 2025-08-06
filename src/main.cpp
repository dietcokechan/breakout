#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;
  const int pWidth = 160;
  const int pHeight = 20;
  const int bRadius = 16;

  int pRectX = (screenWidth - pWidth) / 2;
  int pRectY = (screenHeight - pHeight) / 2;

  int bPosX = (screenWidth - bRadius) / 2;
  int bPosY = (screenHeight - bRadius) / 2;

  int direction = 1;
  float speed = 5.0f;

  InitWindow(screenWidth, screenHeight, "Breakout");
  
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    /************/
    /** Update **/
    /************/
    // move ball side to side
    bPosX += direction * speed;

    if (bPosX + bRadius >= screenWidth || bPosX - bRadius <= 0) {
      direction *= -1;
    }
    
    // player input
    if (IsKeyDown(KEY_RIGHT)) pRectX += 5.0f;
    if (IsKeyDown(KEY_LEFT)) pRectX -= 5.0f;
    
    /**********/
    /** Draw **/
    /**********/
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // player rect
    DrawRectangle(pRectX, pRectY + 200, pWidth, pHeight, BLACK);

    // ball
    DrawCircle(bPosX, bPosY + 100, bRadius, RED);
    
    EndDrawing();
  }
  
  CloseWindow();
  
  return 0;
}
