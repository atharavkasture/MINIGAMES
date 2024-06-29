#include <stdio.h>
#include <SDL.h>
#include "constants.h"
// Define global variables
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
GameState game_state = PONG;
// Other global variables for Pong
int game_is_running = FALSE;
int previous_frame_time = 0;
// Pong game structures and variables
struct ball {
 float x;
 float y;
 float width;
 float height;
 float dx;
 float dy;
} ball;
struct paddle {
 float x;
 float y;
 float width;
 float height;
 float dy;
};
struct paddle left_paddle;
struct paddle right_paddle;
int left_score = 0;
int right_score = 0;
int initialize_window(void) {
 if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
 fprintf(stderr, "ERROR INITIALIZING SDL\n");
 return FALSE;
 }
 window = SDL_CreateWindow("Ping Pong Game", SDL_WINDOWPOS_CENTERED, 
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
void setup_pong(void) {
 printf("Left Score\t");
 printf("Right Score\n");
 ball.width = 15;
 ball.height = 15;
 ball.x = WINDOW_WIDTH / 2 - ball.width / 2;
 ball.y = WINDOW_HEIGHT / 2 - ball.height / 2;
 ball.dx = 350;
 ball.dy = 350;
 left_paddle.x = 20;
 left_paddle.y = WINDOW_HEIGHT / 2 - 50;
 left_paddle.width = 10;
 left_paddle.height = 100;
 left_paddle.dy = 370;
 right_paddle.x = WINDOW_WIDTH - 30;
 right_paddle.y = WINDOW_HEIGHT / 2 - 50;
 right_paddle.width = 10;
 right_paddle.height = 100;
 right_paddle.dy = 370;
}
void process_input_pong(void) {
 SDL_Event event;
 SDL_PollEvent(&event);
 switch (event.type) {
 case SDL_QUIT:
 game_is_running = FALSE;
 break;
 case SDL_KEYDOWN:
 if (event.key.keysym.sym == SDLK_ESCAPE) {
 game_is_running = FALSE;
 }
 else if (event.key.keysym.sym == SDLK_2) {
 game_state = SNAKE;
 game_is_running = FALSE;
 }
 break;
 }
}
void update_pong(void) {
 float delta_time = (SDL_GetTicks() - previous_frame_time) / 1000.0f;
 previous_frame_time = SDL_GetTicks();
 ball.x += ball.dx * delta_time;
 ball.y += ball.dy * delta_time;
 const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
 if (currentKeyStates[SDL_SCANCODE_W]) {
 if (left_paddle.y > 0) {
 left_paddle.y -= left_paddle.dy * delta_time;
 }
 }
 if (currentKeyStates[SDL_SCANCODE_S]) {
 if (left_paddle.y + left_paddle.height < WINDOW_HEIGHT) {
 left_paddle.y += left_paddle.dy * delta_time;
 }
 }
 if (currentKeyStates[SDL_SCANCODE_UP]) {
 if (right_paddle.y > 0) {
 right_paddle.y -= right_paddle.dy * delta_time;
 }
 }
 if (currentKeyStates[SDL_SCANCODE_DOWN]) {
 if (right_paddle.y + right_paddle.height < WINDOW_HEIGHT) {
 right_paddle.y += right_paddle.dy * delta_time;
 }
 }
 if (ball.y <= 0 || ball.y >= WINDOW_HEIGHT - ball.height) {
 ball.dy *= -1;
 }
 if (ball.x <= 0 || ball.x >= WINDOW_WIDTH - ball.width) {
 if (ball.x <= 0) {
 right_score++;
 }
 else {
 left_score++;
 }
 printf("%d\t\t%d\n", left_score, right_score);
 ball.x = WINDOW_WIDTH / 2 - ball.width / 2;
 ball.y = WINDOW_HEIGHT / 2 - ball.height / 2;
 }
 if (ball.x < left_paddle.x + left_paddle.width &&
 ball.x + ball.width > left_paddle.x &&
 ball.y < left_paddle.y + left_paddle.height &&
 ball.y + ball.height > left_paddle.y) {
 ball.dx *= -1;
 }
 if (ball.x < right_paddle.x + right_paddle.width &&
 ball.x + ball.width > right_paddle.x &&
 ball.y < right_paddle.y + right_paddle.height &&
 ball.y + ball.height > right_paddle.y) {
 ball.dx *= -1;
 }
}
void render_pong(void) {
 SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
 SDL_RenderClear(renderer);
 SDL_Rect left_paddle_rect = { (int)left_paddle.x, (int)left_paddle.y, 
(int)left_paddle.width, (int)left_paddle.height };
 SDL_Rect right_paddle_rect = { (int)right_paddle.x, (int)right_paddle.y, 
(int)right_paddle.width, (int)right_paddle.height };
 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
 SDL_RenderFillRect(renderer, &left_paddle_rect);
 SDL_RenderFillRect(renderer, &right_paddle_rect);
 SDL_Rect ball_rect = { (int)ball.x, (int)ball.y, (int)ball.width, 
(int)ball.height };
 SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
 SDL_RenderFillRect(renderer, &ball_rect);
 SDL_RenderPresent(renderer);
}
void main_pong(void) {
 game_is_running = initialize_window();
 setup_pong();
 while (game_is_running) {
 process_input_pong();
 update_pong();
 render_pong();
 }
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 if (game_state == SNAKE) {
 extern void main_snake(void);
 main_snake();
 }
}
int main(void) {
 main_pong();
 return 0;
}
