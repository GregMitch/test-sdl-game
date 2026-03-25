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

    /* Just shown as an example
    if (!SDL_SetTextureScaleMode(g->text_image, SDL_SCALEMODE_NEAREST))
    {
        fprintf(stderr, "Error setting texture scale mode: %s\n", SDL_GetError());
        return false;
    }
    */

    /*
    Load Audio base on example from https://examples.libsdl.org/SDL3_mixer/basics/01-load-and-play/
    */
    g->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (!g->mixer) {
        fprintf(stderr, "Error creating mixer on default device: %s", SDL_GetError());
        return false;
    }

    g->audio1 = MIX_LoadAudio(g->mixer, "sounds/C.ogg", false);
    if (!g->audio1) {
        fprintf(stderr, "Error creating audio: %s", SDL_GetError());
        return false;
    }
    g->track1 = MIX_CreateTrack(g->mixer);
    if (!g->track1) {
        fprintf(stderr, "Error creating mixer track: %s", SDL_GetError());
        return false;
    }
    MIX_SetTrackAudio(g->track1, g->audio1);
    

    g->audio2 = MIX_LoadAudio(g->mixer, "sounds/SDL.ogg", false);
    if (!g->audio2) {
        fprintf(stderr, "Error creating audio2: %s", SDL_GetError());
        return false;
    }
    g->track2 = MIX_CreateTrack(g->mixer);
    if (!g->track2) {
        fprintf(stderr, "Error creating mixer track2: %s", SDL_GetError());
        return false;
    }
    MIX_SetTrackAudio(g->track2, g->audio2);


    g->music = MIX_LoadAudio(g->mixer, "sounds/freesoftwaresong-8bit.ogg", false);
    if (!g->music) {
        fprintf(stderr, "Error creating music audio: %s", SDL_GetError());
        return false;
    }
    g->music_track = MIX_CreateTrack(g->mixer);
    if (!g->music_track) {
        fprintf(stderr, "Error creating mixer music_track: %s", SDL_GetError());
        return false;
    }
    MIX_SetTrackAudio(g->music_track, g->music);

    return true;
}
