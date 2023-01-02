#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define NUM_CARS 4
#define NUM_CITIES 4

const char* city_names[NUM_CITIES] = { "Paris", "London", "New York", "Tokyo" };

struct Car {
  int x;
  int y;
  int speed;
  char name[32];
  SDL_Texture* texture;
};

struct City {
  char name[32];
  SDL_Texture* background;
  SDL_Texture* foreground;
  struct Car cars[NUM_CARS];
};

struct GameState {
  bool running;
  SDL_Window* window;
  SDL_Renderer* renderer;
  int current_city;
  struct City cities[NUM_CITIES];
};

bool init_game(struct GameState* game) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
    fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    return false;
  }

  game->window = SDL_CreateWindow(
      "Supercar Racing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (game->window == NULL) {
    fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
    return false;
  }

  game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
  if (game->renderer == NULL) {
    fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

bool load_textures(struct GameState* game) {
  for (int i = 0; i < NUM_CITIES; i++) {
    char path[256];
    sprintf(path, "textures/%s_bg.png", city_names[i]);
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
      fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
      return false;
    }
    game->cities[i].background = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    sprintf(path, "textures/%s_fg.png", citynames[i]);
surface = IMG_Load(path);
if (surface == NULL) {
fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
return false;
}
game->cities[i].foreground = SDL_CreateTextureFromSurface(game->renderer, surface);
SDL_FreeSurface(surface);
    
for (int j = 0; j < NUM_CARS; j++) {
  sprintf(path, "textures/car%d.png", j + 1);
  surface = IMG_Load(path);
  if (surface == NULL) {
    fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
    return false;
  }
  game->cities[i].cars[j].texture = SDL_CreateTextureFromSurface(game->renderer, surface);
  SDL_FreeSurface(surface);
}
}

return true;
}

void cleanup_game(struct GameState* game) {
for (int i = 0; i < NUM_CITIES; i++) {
SDL_DestroyTexture(game->cities[i].background);
SDL_DestroyTexture(game->cities[i].foreground);
for (int j = 0; j < NUM_CARS; j++) {
SDL_DestroyTexture(game->cities[i].cars[j].texture);
}
}
SDL_DestroyRenderer(game->renderer);
SDL_DestroyWindow(game->window);
SDL_Quit();
}

int main(int argc, char** argv) {
struct GameState game;
game.running = true;
game.current_city = 0;

if (!init_game(&game)) {
return 1;
}
if (!load_textures(&game)) {
cleanup_game(&game);
return 1;
}

for (int i = 0; i < NUM_CITIES; i++) {
strcpy(game.cities[i].name, city_names[i]);
for (int j = 0; j < NUM_CARS; j++) {
sprintf(game.cities[i].cars[j].name, "Car %d", j + 1);
game.cities[i].cars[j].x = rand() % SCREEN_WIDTH;
game.cities[i].cars[j].y = rand() % SCREEN_HEIGHT;
game.cities[i].cars[j].speed = rand() % 5 + 5;
}
}

while (game.running) {
SDL_Event event;
while (SDL_PollEvent(&event)) {
switch (event.type) {
case SDL_QUIT:
game.running = false;
break;
case SDL_KEYDOWN:
if (event.key.keysym.sym == SDLK_ESCAPE) {
game.running = false;
}
break;
default:
break;
}
}

SDL_RenderClear
