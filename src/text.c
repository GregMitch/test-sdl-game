#include "text.h"

bool text_new(struct Text **text, SDL_Renderer *renderer)
{
	*text = calloc(1, sizeof(struct Text));

	if (*text == NULL)
	{
		fprintf(stderr, "Error Calloc of New Text.\n");
		return false;
	}
	
	//Allows us to avoid dereferencing text for rest of function
	struct Text *t = *text;

    t->renderer = renderer;

    TTF_Font *font = TTF_OpenFont("fonts/freesansbold.ttf", TEXT_SIZE);
	if (!font)
	{
		fprintf(stderr, "Error opening font: %s\n", SDL_GetError());
		return false;
	}

	SDL_Surface *surf = TTF_RenderText_Blended(font, TEXT_STR, 0, WHITE_COLOUR);
    TTF_CloseFont(font);
    font = NULL;
	if (!surf)
	{
		fprintf(stderr, "Error rendering text to surface: %s\n", SDL_GetError());
		return false;
	}

	t->rect.w = (float)surf->w;
	t->rect.h = (float)surf->h;

	t->image = SDL_CreateTextureFromSurface(t->renderer, surf);
	SDL_DestroySurface(surf);
	surf = NULL;
	if (!t->image)
	{
		fprintf(stderr, "Error creating text texture %s\n", SDL_GetError());
		return false;
	}

    t->x_vel = TEXT_VELOCITY;
    t->y_vel = TEXT_VELOCITY;

	return true;
}

void text_free(struct Text **text)
{
    if (*text)
    {
        struct Text *t = *text;

        if (t->image)
        {
            SDL_DestroyTexture(t->image);
            t->image = NULL;
        }

        t->renderer = NULL;

        free(t);
        t = NULL;
        *text = NULL;

        printf("Free text.\n");
    }
}

void text_update(struct Text *t)
{
    t->rect.x += t->x_vel;
    t->rect.y += t->y_vel;

    if (t->rect.x + t->rect.w > WINDOW_WIDTH)
    {
        //Example of clamping
        //t->rect.x = WINDOW_WIDTH - t->rect.w;
        t->x_vel = -TEXT_VELOCITY;
    }
    else if (t->rect.x < 0)
    {
        t->x_vel = TEXT_VELOCITY;
    }

    if (t->rect.y + t->rect.h > WINDOW_HEIGHT)
    {
        //Example of clamping
        //t->rect.y = WINDOW_HEIGHT - t->rect.h;
        t->y_vel = -TEXT_VELOCITY;
    }
    else if (t->rect.y < 0)
    {
        t->y_vel = TEXT_VELOCITY;
    }
}

void text_draw(const struct Text *t)
{
    SDL_RenderTexture(t->renderer, t->image, NULL, &t->rect);
}