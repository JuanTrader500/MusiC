#ifndef AUDIO_H
#define AUDIO_H

//Librerias relebantes para nuesto reproductor de mp3
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// Prototipos de funciones para usarlas en el .cpp
void initAudio();
void reproducirMusica(const char *rutaArchivo);
void cerrarAudio();

#endif