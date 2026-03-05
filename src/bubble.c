#include "bubble.h"

SDL_Surface *bubble_create_text(const char *str, float size, int radius, SDL_Color inner, SDL_Color outer)
{
    TTF_Font *font = TTF_OpenFont("fonts/freesansbold.ttf", TEXT_SIZE);
    if (!font)
    {
        fprintf(stderr, "Error opening font: %s\n", SDL_GetError());
        return false;
    }
}