#include "bubble.h"

void blit_symmetric_points(SDL_Surface *src_surf, SDL_Surface *target_surf, int radius, int x, int y);

SDL_Surface *solid_colour_surface(SDL_Surface *src_surf, SDL_Color colour);

void blit_symmetric_points(SDL_Surface *src_surf, SDL_Surface *target_surf, int radius, int x, int y)
{
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius + x, radius + y, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius + x, radius - y, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius - x, radius + y, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius - x, radius - y, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius + y, radius + x, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius + y, radius - x, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius - y, radius + x, src_surf->w, src_surf->h});
    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius - y, radius - x, src_surf->w, src_surf->h});
}

SDL_Surface *solid_colour_surface(SDL_Surface *src_surf, SDL_Color colour)
{
    if (!src_surf)
    {
        fprintf(stderr, "Error surface is null");
    }

    SDL_Surface *colour_surf = SDL_DuplicateSurface(src_surf);
    if (!colour_surf)
    {
        fprintf(stderr, "Error copying surface: %s\n", SDL_GetError());
        return NULL;
    }
    
    if (!SDL_LockSurface(colour_surf))
    {
        fprintf(stderr, "Error locking surface: %s\n", SDL_GetError());
        SDL_DestroySurface(colour_surf);
        return NULL;
    }

    int width = colour_surf->w;
    int height = colour_surf->h;

    const SDL_PixelFormatDetails *format_details = SDL_GetPixelFormatDetails(colour_surf->format);
    if (!format_details)
    {
        fprintf(stderr, "Error getting format details: %s\n", SDL_GetError());
        SDL_DestroySurface(colour_surf);
        return NULL;
    }

    if (format_details->bits_per_pixel != 32)
    {
        fprintf(stderr, "Surface is not 32 bits. Aborting.\n");
        SDL_DestroySurface(colour_surf);
        return NULL;
    }

    //Should not need to check if NULL due to check on line 24
    Uint32 *pixels = (Uint32 *)colour_surf->pixels;
    SDL_Palette *palette = SDL_GetSurfacePalette(colour_surf);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Uint32 pixel = pixels[(y * width) + x];
            Uint8 r;
            Uint8 g;
            Uint8 b;
            Uint8 a;
            SDL_GetRGBA(pixel, format_details, palette, &r, &g, &b, &a);

            if (a > 0)
            {
                // Don't care about changing the alpha
                pixel = SDL_MapRGBA(format_details, palette, colour.r, colour.g, colour.b, a);
                pixels[(y * width) + x] = pixel;
            }
        }
    }

    SDL_UnlockSurface(colour_surf);

    return colour_surf;
}

SDL_Surface *bubble_surface(SDL_Surface *src_surf, int radius, SDL_Color outer_colour)
{
    if (!src_surf)
    {
        fprintf(stderr, "Passed null surface: %s\n", SDL_GetError());
        return NULL;
    }

    int width = src_surf->w + (radius * 2);
    int height = src_surf->h + (radius * 2);

    SDL_Surface *target_surf = SDL_CreateSurface(width, height, src_surf->format);
    if (!target_surf)
    {
        fprintf(stderr, "Error creating new surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *outer_surf = solid_colour_surface(src_surf, outer_colour);
    if (!outer_surf)
    {
        fprintf(stderr, "Error creating outer surface: %s\n", SDL_GetError());
        SDL_DestroySurface(target_surf);
        return NULL;
    }

    // // Polar Coordinate Trigonometry Algorithm -> requires math library
    // for (int index = 0; index < (2 * M_PI * radius); index++)
    // {
    //     double rad = (double)index / radius;
    //     int x = (int)(cos(rad) * radius) + radius;
    //     int y = (int)(sin(rad) * radius) + radius;
        
    //     SDL_BlitSurface(outer_surf, NULL, target_surf, &(SDL_Rect){x, y, outer_surf->w, outer_surf->h});
    // }

    // Bresenham's Circle Drawing Algorithm -> does not require math library
    int x = 0;
    int y = radius;
    int d = 3 - (2 * radius);
    blit_symmetric_points(outer_surf, target_surf, radius, x, y);
    while( y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;   
        }
        else
        {
            d = d + 4 * x + 6;
        }
        
        blit_symmetric_points(outer_surf, target_surf, radius, x, y);
    }

    SDL_BlitSurface(src_surf, NULL, target_surf, &(SDL_Rect){radius, radius, src_surf->w, src_surf->h});
    SDL_DestroySurface(outer_surf);

    return target_surf;
}

SDL_Surface *bubble_create_text(const char *str, float size, int radius, SDL_Color inner_colour, SDL_Color outer_colour)
{
    //If you pass relative path, must run binary from root of repo. Absolute path fixes this
    TTF_Font *font = TTF_OpenFont("fonts/freesansbold.ttf", TEXT_SIZE);
    if (!font)
    {
        fprintf(stderr, "Error opening font: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *text_surf = TTF_RenderText_Blended(font, str, 0, inner_colour);
    TTF_CloseFont(font);
    font = NULL;
    if (!text_surf)
    {
        fprintf(stderr, "Error rendering text to surface: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *bubble_surf = bubble_surface(text_surf, radius, outer_colour);
    SDL_DestroySurface(text_surf);
    text_surf = NULL;
    if (!bubble_surf)
    {
        return NULL;
    }

    return bubble_surf;
}