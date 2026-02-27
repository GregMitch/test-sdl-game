cmake_minimum_required(VERSION 3.16)
project(main)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Generate compile_commands.json for clangd lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in vendored/SDL_image
set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_JPEG OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_PNG_LIBPNG OFF)    # SDL3 includes built-in support for loading PNGs. If you need more than what that supports, enable this option.
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# This assumes the SDL_mixer source is available in vendored/SDL_mixer
set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
set(SDLMIXER_GME OFF)
set(SDLMIXER_WAVPACK OFF)     
set(SDLMIXER_MOD OFF)
set(SDLMIXER_MOD_XMP OFF)
set(SDLMIXER_OPUS OFF)
set(SDLMIXER_MP3_MPG123 OFF)
set(SDLMIXER_VORBIS_VORBISFILE OFF)
set(SDLMIXER_FLAC_LIBFLAC OFF)
add_subdirectory(vendored/SDL_mixer EXCLUDE_FROM_ALL)

# My src files
set(SOURCES
	src/main.c
	src/game.c
	src/init_sdl.c
	src/load_media.c
)

# Create your game executable target as usual
add_executable(main ${SOURCES})

# My header files
target_include_directories(main PRIVATE src)

# Link to the actual SDL3 library.
target_link_libraries(main PRIVATE SDL3_mixer::SDL3_mixer SDL3_image::SDL3_image SDL3::SDL3)

