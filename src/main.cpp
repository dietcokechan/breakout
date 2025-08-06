#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BRICK_ROWS 6
#define BRICKS_PER_ROW 12

// structs
typedef struct Player {
  Vector2 pos;
  Vector2 size;
} Player;

typedef struct Ball {
  Vector2 pos;
  Vector2 speed;
  int radius;
} Ball;

typedef struct Brick {
  Vector2 pos;
} Brick;

// global variables
static Player player = { 0 };
static Ball ball = { 0 };
static Brick brick[BRICK_ROWS][BRICKS_PER_ROW];

static Color colors[3] = {DARKBLUE, BLUE, SKYBLUE};
static Vector2 brickSize = { 0 };
static const int brickPadding = 6;

// functions
static void InitGame();
static void UpdateGame();
static void DrawGame();

// initialization
void InitGame() {
  // init player
  player.size = (Vector2){ SCREEN_WIDTH / 8, 20 };
  player.pos = (Vector2){ (SCREEN_WIDTH - player.size.x) / 2, (SCREEN_HEIGHT - player.size.y) / 2 };

  // init ball
  ball.radius = 10;
  ball.pos = (Vector2){ player.pos.x, player.pos.y - player.size.y / 2 - ball.radius };
  ball.speed = (Vector2){ 0, 0 };

  // init bricks
  brickSize = (Vector2){ SCREEN_WIDTH / BRICKS_PER_ROW, 26};
  int initialPos = 60;
  
  for (int i = 0; i < BRICK_ROWS; i++) {
    int paddingX = brickSize.x / 2 + brickPadding;
    
    for (int j = 0; j < BRICKS_PER_ROW; j++) {
      brick[i][j].pos.x = j * brickSize.x + paddingX;
      brick[i][j].pos.y = i * brickSize.y + initialPos;
      
      paddingX += brickPadding;
    }
    initialPos += brickPadding;
  }
}

// update
void UpdateGame() {
  // ball movement
  if (ball.pos.x + ball.radius >= SCREEN_WIDTH || ball.pos.x - ball.radius <= 0) {
    ball.speed.x *= -1;
  }
  else if (ball.pos.y + ball.radius >= SCREEN_HEIGHT || ball.pos.y - ball.radius <= 0) {
    ball.speed.y *= -1;
  }

  if (IsKeyPressed(KEY_SPACE)) {
    ball.speed = (Vector2){ 0, -5 };
  }
  ball.pos.x += ball.speed.x;
  ball.pos.y += ball.speed.y;
  

  // player movement (restrict to window)
  if (IsKeyDown(KEY_RIGHT)) {
    player.pos.x += 5.0f;
  }
  if (player.pos.x + player.size.x / 2 >= SCREEN_WIDTH) {
    player.pos.x = SCREEN_WIDTH - player.size.x / 2;
  }

  if (IsKeyDown(KEY_LEFT)) {
    player.pos.x -= 5.0f;
  }
  if (player.pos.x - player.size.x <= 0) {
    player.pos.x = player.size.x / 2;
  }
}

// drawing
void DrawGame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  
  // draw player rect
  DrawRectangle(player.pos.x, player.pos.y + 200, player.size.x, player.size.y, BLACK);

  // draw ball
  DrawCircle(ball.pos.x, ball.pos.y + 100, ball.radius, MAROON);

  // draw bricks
  for (int i = 0; i < BRICK_ROWS; i++) {
    Color brickColor = colors[i % 3];
    for (int j = 0; j < BRICKS_PER_ROW; j++) {
      DrawRectangle(brick[i][j].pos.x - brickSize.x / 2, brick[i][j].pos.y - brickSize.y / 2, brickSize.x, brickSize.y, brickColor);
    }
  }
  
  DrawFPS(10, 10);
  EndDrawing();
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout");
  SetTargetFPS(60);
  InitGame();
  
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }
  
  CloseWindow();
  
  return 0;
}
