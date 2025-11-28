#ifndef TABLASHASH_H
#define TABLASHASH_H
#include "lista.h"
#define Tamaño_Tabla 101

typedef struct NodoHash{
    NodoCancion* datosCancion;
    struct NodoHash* siguiente;
}NodoHash;

void inicializarHash();
void insertarHash(NodoCancion* nuevaCancion);
NodoCancion* buscarPorHash(const char* titulo);
void eliminarPorHash(const char* titulo);
void liberarHash();
void imprimirHash();

#endif