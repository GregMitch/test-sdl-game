#ifndef BUBBLE_H
#define BUBBLE_H

#include "main.h"

//void blit_symmetric_points(SDL_Surface *src_surf, SDL_Surface *target_src, int radius, int x, int y);
SDL_Surface *bubble_create_text(const char *str, float size, int radius, SDL_Color inner_colour, SDL_Color outer_colour);

SDL_Surface *bubble_surface(SDL_Surface *src_surf, int radius, SDL_Color colour);

#endif