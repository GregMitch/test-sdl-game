#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "player.h"
#include "text.h"

struct Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    struct Player *player;
    struct Text *text;
    SDL_Event event;
    bool is_running;
    
    //Audio stuff
    MIX_Mixer *mixer;
    MIX_Audio *audio1;
    MIX_Track *track1;
    MIX_Audio *audio2;
    MIX_Track *track2;
    MIX_Audio *music;
    MIX_Track *music_track;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
