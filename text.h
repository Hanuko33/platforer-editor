#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL.h>
int load_font();
void write_text(int x, int y, const char * text, SDL_Color color, int scale, SDL_Window* window, SDL_Renderer* renderer);

#endif
