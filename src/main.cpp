#include "raylib.h"
#include <cmath>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BRICK_ROWS 4
#define BRICKS_PER_ROW 12

// structs
typedef struct Player {
  Vector2 initialPos;
  Vector2 pos;
  Vector2 size;
} Player;

typedef struct Ball {
  Vector2 initialPos;
  Vector2 pos;
  Vector2 speed;
  int radius;
} Ball;

typedef struct Brick {
  Vector2 pos;
  bool active;
} Brick;

// global variables
static Player player = { 0 };
static Ball ball = { 0 };
static Brick brick[BRICK_ROWS][BRICKS_PER_ROW];

static Color colors[3] = {DARKBLUE, BLUE, SKYBLUE};
static Vector2 brickSize = { 0 };
static int inactiveBricks = 0;

static bool gameOver = false;
static bool won = false;

static Sound hitSound;
static Sound loseSound;
static Sound winSound;

// functions
static void InitGame();
static void UpdateGame();
static void DrawGame();
static void CollisionChecks();
static void LoadGame();
static void UnloadGame();

void LoadGame() {
  InitAudioDevice();

  // load sounds
  hitSound = LoadSound("../audio/hit.wav");
  loseSound = LoadSound("../audio/lose.wav");
  winSound = LoadSound("../audio/win.wav");
}

void UnloadGame() {
  CloseAudioDevice();
}

// check for ball collision with player/bricks
void CollisionChecks() {
  // ball collision with player
  Rectangle playerRect = (Rectangle){ player.pos.x - player.size.x / 2, player.pos.y - player.size.y / 2, player.size.x, player.size.y };
  if (CheckCollisionCircleRec(ball.pos, ball.radius, playerRect)) {
    if (ball.speed.y > 0) {
      ball.speed.y *= -1;
      ball.speed.x = (ball.pos.x - player.pos.x) / (player.size.x / 2) * 5;
    }
  }

  // ball collision with bricks
  for (auto & i : brick) {
    for (auto & j : i) {
      if (j.active) {
        // hit down
        if (((ball.pos.y - ball.radius) <= (j.pos.y + brickSize.y/2)) &&
            ((ball.pos.y - ball.radius) > (j.pos.y + brickSize.y/2 + ball.speed.y)) &&
            ((std::fabs(ball.pos.x - j.pos.x)) < (brickSize.x/2 + ball.radius * 2/3)) && (ball.speed.y < 0))
        {
          j.active = false;
          inactiveBricks++;
          ball.speed.y *= -1;
          PlaySound(hitSound);
        }
        // hit up
        else if (((ball.pos.y + ball.radius) >= (j.pos.y - brickSize.y/2)) &&
                ((ball.pos.y + ball.radius) < (j.pos.y - brickSize.y/2 + ball.speed.y)) &&
                ((std::fabs(ball.pos.x - j.pos.x)) < (brickSize.x/2 + ball.radius * 2/3)) && (ball.speed.y > 0))
        {
          j.active = false;
          inactiveBricks++;
          ball.speed.y *= -1;
          PlaySound(hitSound);
        }
        // hit left
        else if (((ball.pos.x + ball.radius) >= (j.pos.x - brickSize.x/2)) &&
                ((ball.pos.x + ball.radius) < (j.pos.x - brickSize.x/2 + ball.speed.x)) &&
                ((std::fabs(ball.pos.y - j.pos.y)) < (brickSize.y/2 + ball.radius * 2/3)) && (ball.speed.x > 0))
        {
          j.active = false;
          inactiveBricks++;
          ball.speed.x *= -1;
          PlaySound(hitSound);
        }
        // hit right
        else if (((ball.pos.x - ball.radius) <= (j.pos.x + brickSize.x/2)) &&
                ((ball.pos.x - ball.radius) > (j.pos.x + brickSize.x/2 + ball.speed.x)) &&
                ((std::fabs(ball.pos.y - j.pos.y)) < (brickSize.y/2 + ball.radius * 2/3)) && (ball.speed.x < 0))
        {
          j.active = false;
          inactiveBricks++;
          ball.speed.x *= -1;
          PlaySound(hitSound);
        }
      }
    }
  }
}

// initialization
void InitGame() {
  // init player
  player.size = (Vector2){ SCREEN_WIDTH / 10, 20 };
  player.pos = player.initialPos = (Vector2){ (SCREEN_WIDTH - player.size.x) / 2, SCREEN_HEIGHT * 0.9 };

  // init ball
  ball.radius = 10;
  ball.pos = ball.initialPos = (Vector2){ player.pos.x, player.pos.y - player.size.y / 2 - ball.radius };
  ball.speed = (Vector2){ 0, 0 };

  // init bricks
  brickSize = (Vector2){ SCREEN_WIDTH / BRICKS_PER_ROW, 40};
  int initialPos = 60;
  
  for (int i = 0; i < BRICK_ROWS; i++) {
    for (int j = 0; j < BRICKS_PER_ROW; j++) {
      brick[i][j].pos.x = j * brickSize.x + brickSize.x / 2;
      brick[i][j].pos.y = i * brickSize.y + initialPos;
      brick[i][j].active = true;
    }
  }
}

// update
void UpdateGame() {
  if (!gameOver && !won) {
    // ball movement
    if (ball.pos.x + ball.radius >= SCREEN_WIDTH || ball.pos.x - ball.radius <= 0) {
      ball.speed.x *= -1;
    }
    if (ball.pos.y - ball.radius <= 0) {
      ball.speed.y *= -1;
    }
    if (ball.pos.y + ball.radius >= SCREEN_HEIGHT) {
      ball.speed = (Vector2){ 0, 0 };
      gameOver = true;
      PlaySound(loseSound);
    }

    // start game
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
      player.pos.x = SCREEN_WIDTH - (player.size.x / 2);
    }

    if (IsKeyDown(KEY_LEFT)) {
      player.pos.x -= 5.0f;
    }
    if (player.pos.x - player.size.x / 2 <= 0) {
      player.pos.x = (player.size.x / 2);
    }

    CollisionChecks();

    if (inactiveBricks >= BRICK_ROWS * BRICKS_PER_ROW) {
      won = true;
      PlaySound(winSound);
    }
    else won = false;
  }
  else {
    if (IsKeyPressed(KEY_SPACE)) {
      InitGame();
      gameOver = false;
      won = false;
      inactiveBricks = 0;
    }
  }
}

// drawing
void DrawGame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (!gameOver && !won) {
    // draw player rect
    DrawRectangle(player.pos.x - player.size.x / 2, player.pos.y - player.size.y / 2, player.size.x, player.size.y, BLACK);

    // draw ball
    DrawCircleV(ball.pos, ball.radius, MAROON);

    // draw bricks
    for (int i = 0; i < BRICK_ROWS; i++) {
      for (int j = 0; j < BRICKS_PER_ROW; j++) {
        if (brick[i][j].active) {
          Color brickColor = colors[(i + j) % 3];
          DrawRectangle(brick[i][j].pos.x - brickSize.x / 2, brick[i][j].pos.y - brickSize.y / 2, brickSize.x, brickSize.y, brickColor);
        }
      }
    }
  }
  else if (won) {
    DrawText("Y0U WON! \nPRESS [SPACE] TO PLAY AGAIN", SCREEN_WIDTH / 2 - MeasureText("Y0U WON! \nPRESS [SPACE] TO PLAY AGAIN", 20) / 2, SCREEN_HEIGHT / 2 - 50, 20, DARKGRAY);
  }
  else {
    DrawText("PRESS [SPACE] TO PLAY AGAIN", SCREEN_WIDTH / 2 - MeasureText("PRESS [SPACE] TO PLAY AGAIN", 20) / 2, SCREEN_HEIGHT / 2 - 50, 20, DARKGRAY);
  }
  
  DrawFPS(10, 10);
  EndDrawing();
}

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout");
  SetTargetFPS(60);
  LoadGame();
  InitGame();
  
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }

  UnloadGame();
  CloseWindow();
  
  return 0;
}
