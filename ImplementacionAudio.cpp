#include "audio.h"

// Variable estatica (solo visible en este archivo para protección)
static Mix_Music *musicaActual = NULL;

void initAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Error SDL: %s\n", SDL_GetError());
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Error Mixer: %s\n", Mix_GetError());
        exit(1);
    }
    printf("Sistema de Audio Inicializado.\n");
}

void reproducirMusica(const char *rutaArchivo) {
    if (musicaActual != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(musicaActual);
        musicaActual = NULL;
    }

    musicaActual = Mix_LoadMUS(rutaArchivo);
    
    if (musicaActual == NULL) {
        printf("Error cargando MP3 (%s): %s\n", rutaArchivo, Mix_GetError());
        return;
    }

    Mix_PlayMusic(musicaActual, 1);
    printf("Reproduciendo: %s\n", rutaArchivo);
}

void cerrarAudio() {
    if (musicaActual != NULL) {
        Mix_FreeMusic(musicaActual);
    }
    Mix_CloseAudio();
    SDL_Quit();
    printf("Audio cerrado correctamente.\n");
}