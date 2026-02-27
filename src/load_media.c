#include "load_media.h"

bool game_load_media(struct Game *g)
{
	/* Commented out because my image has no background, so can't see colour changing.
	g->background = IMG_LoadTexture(g->renderer, "images/cyberpunk.png");
	if (!g->background)
	{
		fprintf(stderr, "Error loading texture: %s\n", SDL_GetError());
		return false;
	}
	*/

	return true;
}
