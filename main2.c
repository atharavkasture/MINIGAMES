#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "constants.h"
typedef struct {
 int x, y;
} Position;
// Global variables for Snake
int running = FALSE;
Position apple;
Position snake[100];
int snakeLength = 1;
int dx = 1, dy = 0;
int init(void);
void generateApple(void);
void handleInput(void);
void update(void);
void render(void);
void setup_snake(void);
void main_snake(void);
int main(){
  main_snake();
  return 0;
}
int init(void) {
 if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
 fprintf(stderr, "ERROR INITIALIZING SDL\n");
 return FALSE;
 }
 window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, 
SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
 if (!window) {
 fprintf(stderr, "ERROR CREATING WINDOW\n");
 return FALSE;
 }
 renderer = SDL_CreateRenderer(window, -1, 0);
 if (!renderer) {
 fprintf(stderr, "ERROR RENDERING WINDOW\n");
 return FALSE;
 }
 return TRUE;
}
void generateApple(void) {
 srand(time(NULL));
 apple.x = (rand() % (WINDOW_WIDTH / CELL_SIZE)) * CELL_SIZE;
 apple.y = (rand() % (WINDOW_HEIGHT / CELL_SIZE)) * CELL_SIZE;
}
void handleInput(void) {
 SDL_Event event;
 while (SDL_PollEvent(&event)) {
 if (event.type == SDL_QUIT) {
 running = FALSE;
 }
 else if (event.type == SDL_KEYDOWN) {
 switch (event.key.keysym.sym) {
 case SDLK_UP:
 if (dy != 1) {
 dx = 0;
dy = -1;
 }
 break;
 case SDLK_DOWN:
 if (dy != -1) {
 dx = 0;
dy = 1;
 }
 break;
 case SDLK_LEFT:
 if (dx != 1) {
 dx = -1;
dy = 0;
 }
 break;
 case SDLK_RIGHT:
 if (dx != -1) {
 dx = 1;
dy = 0;
 }
 break;
 case SDLK_ESCAPE:
 running = FALSE;
 break;
 case SDLK_1:
 game_state = PONG;
 running = FALSE;
 break;
 }
 }
 }
}
void update(void) {
 for (int i = snakeLength - 1; i > 0; --i) {
 snake[i] = snake[i - 1];
 }
 snake[0].x += dx * CELL_SIZE;
 snake[0].y += dy * CELL_SIZE;
 if (snake[0].x < 0 || snake[0].x >= WINDOW_WIDTH || snake[0].y < 0 || snake[0].y 
>= WINDOW_HEIGHT) {
 running = FALSE;
 return;
 }
 for (int i = 1; i < snakeLength; ++i) {
 if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
 running = FALSE;
 return;
 }
 }
 if (snake[0].x == apple.x && snake[0].y == apple.y) {
 snakeLength++;
 generateApple();
 }
}
void render(void) {
 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
 SDL_RenderClear(renderer);
 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
 for (int i = 0; i < snakeLength; ++i) {
 SDL_Rect snakeRect = { snake[i].x, snake[i].y, CELL_SIZE, CELL_SIZE };
 SDL_RenderFillRect(renderer, &snakeRect);
 }
 SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
 SDL_Rect appleRect = { apple.x, apple.y, CELL_SIZE, CELL_SIZE };
 SDL_RenderFillRect(renderer, &appleRect);
 SDL_RenderPresent(renderer);
}
void setup_snake(void) {
 snake[0].x = WINDOW_WIDTH / 2;
 snake[0].y = WINDOW_HEIGHT / 2;
 snakeLength = 1;
 dx = 1;
 dy = 0;
 generateApple();
}
void main_snake(void) {
 running = init();
 setup_snake();
 while (running) {
 handleInput();
 update();
 render();
 SDL_Delay(100); // Control the speed of the game
 }
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 if (game_state == PONG) {
 extern void main_pong(void);
 main_pong();
 }
