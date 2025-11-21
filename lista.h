#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generamos la estructura de nuestro nodo basandonos en nuestro csv
typedef struct NodoCancion {
    char id[16];                
    char titulo[128];
    char ruta[512];  
    char genero[50];            
    int calificacion;
    
    struct NodoCancion* prev;
    struct NodoCancion* next;
} NodoCancion;

// Variables Globales (extern permite que otros archivos las vean, pero se definen en el .cpp)
extern NodoCancion* head;
extern NodoCancion* tail;

// Prototipos de funciones para usarlas en el .cpp
NodoCancion* crearNodo(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion);
void insertEnd(const char* id, const char* titulo, const char* ruta, const char* genero, int calificacion);
void displayForward();
void freeList();

#endif