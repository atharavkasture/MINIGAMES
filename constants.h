#ifndef CONSTANTS_H
#define CONSTANTS_H
#define TRUE 1
#define FALSE 0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define CELL_SIZE 20
#include <SDL.h>
// Declare global variables as extern
extern SDL_Window* window;
extern SDL_Renderer* renderer;
// Define GameState enum
typedef enum {
 PONG,
 SNAKE
} GameState;
extern GameState game_state;
#endif /* CONSTANTS_H */
