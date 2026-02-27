#include "init_sdl.h"

bool game_init_sdl(struct Game *g)
{
	//Proper way to set Icon on my version of Fedora
	SDL_SetHint(SDL_HINT_APP_ID, "com.gregorym.testgame");
	
	if (!SDL_Init(SDL_FLAGS))
	{
		fprintf(stderr, "Error initializing SDL3: %s\n", SDL_GetError());
		return false;
	}

	g->window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!g->window)
	{
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		return false;
	}

	g->renderer = SDL_CreateRenderer(g->window, NULL);
	if (!g->renderer)
	{
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		return false;
	}

	/* 
	 * Not needed due to oddity with Icons on Wayland Gnome Desktops (like Fedora)
	 * Icon is set in above call to SDL_SetHint()
	SDL_Surface *icon_surf = IMG_Load("images/tm.png");
	if (!icon_surf)
	{
		fprintf(stderr, "Error loading surface: %s\n", SDL_GetError());
		return false;
	}

	if (!SDL_SetWindowIcon(g->window, icon_surf))
	{
		fprintf(stderr, "Error setting Window Icon: %s\n", SDL_GetError());
		SDL_DestroySurface(icon_surf);
		return false;
	}

	SDL_DestroySurface(icon_surf);
	*/
	
	return true;
}

