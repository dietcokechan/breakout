#include "raylib.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "Breakout");
  
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("I work!", 350, 250, 32, BLACK);
    
    EndDrawing();
  }
  
  CloseWindow();
  
  return 0;
}
