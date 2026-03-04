# test-sdl-game

## Build
Run following commands: \
    cd into `<root>/vendored/SDL_ttf/external` \
    ./download.sh \
    cmake -S .-B build \
    cmake --build build

Consists of 4 submodules
1. https://github.com/libsdl-org/SDL -> Most SDL files
2. https://github.com/libsdl-org/SDL_image -> SDL image support
3. https://github.com/libsdl-org/SDL_mixer -> SDL audio support
4. https://github.com/libsdl-org/SDL_ttf -> SDL text support

Note 


This is template project made by following *Programming Rainbows Beginners Guide to SDL3 in C*.
https://www.youtube.com/watch?v=Ik4vWquS-d4&list=PLO02jwa2ZaiBaZ2t-sU4i8JttexCRixsn
