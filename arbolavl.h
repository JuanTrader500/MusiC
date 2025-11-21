#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h" // Necesario para referenciar la estructura NodoCancion

// Definición del Nodo AVL
typedef struct NodoAVL {
    // Puntero al nodo de la lista enlazada (contiene todos los datos de la canción)
    NodoCancion* datosCancion; 
    
    struct NodoAVL *izq;
    struct NodoAVL *der;
    int altura;
} NodoAVL;

// Puntero Global a la Raíz del AVL
extern NodoAVL* raizAVL;

// Prototipos de funciones AVL
NodoAVL* insertarAVL(NodoAVL* raiz, NodoCancion* nuevaCancion);
NodoCancion* buscarPorTituloAVL(NodoAVL* raiz, const char* titulo);
void liberarAVL(NodoAVL* raiz);
void inicializarAVL();

#endif