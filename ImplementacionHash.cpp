#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablaHash.h"

static NodoHash* tablaHash[Tamaño_Tabla];

// Funcion hash 
unsigned int hash(const char* str){
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c;
    }
    return hash % Tamaño_Tabla;
}

void inicializarHash(){
    for(int i= 0; i< Tamaño_Tabla; i++){
        tablaHash[i] = NULL;
    }
}

void insertarHash(NodoCancion* nuevaCancion){
    unsigned int indice  = hash(nuevaCancion->titulo);
    NodoHash* nuevo = (NodoHash*)malloc(sizeof(NodoHash));
    if (nuevo == NULL) return;
    nuevo->datosCancion = nuevaCancion;
    nuevo->siguiente = tablaHash[indice]; 
    tablaHash[indice] = nuevo;
}

NodoCancion* buscarPorHash(const char* titulo){
    unsigned int indice = hash(titulo);
    NodoHash* actual = tablaHash[indice];
    
    while (actual != NULL) {
        if(strcmp(actual->datosCancion->titulo, titulo) == 0){
            return actual->datosCancion;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

void eliminarPorHash(const char* titulo){
    unsigned int indice = hash(titulo);
    NodoHash* actual = tablaHash[indice];
    NodoHash* previo = NULL;
    
    while (actual != NULL){
        if(strcmp(actual->datosCancion->titulo, titulo) == 0){
            if(previo == NULL){
                tablaHash[indice] = actual->siguiente;
            }else{
                previo->siguiente = actual->siguiente;
            }
            free(actual);
            printf("Eliminacion correcta del Nodo en la tabla Hash.\n");
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }
}

void liberarHash(){
    for(int i=0; i< Tamaño_Tabla; i++){
        NodoHash* actual = tablaHash[i];
        while (actual != NULL){
            NodoHash* temp = actual; 
            actual = actual->siguiente; 
            free(temp); 
        }
        tablaHash[i] = NULL;
    }
}

void imprimirHash(){
    printf("\n VISUALIZACION DE LA TABLA HASH (TAMAÑO: %d)\n", Tamaño_Tabla);
    int contNodos,indicesocupados = 0;
    for(int i=0; i< Tamaño_Tabla; i++){
        if(tablaHash[i] != NULL){
            indicesocupados++;
            printf("[%03d]: ", i);
            NodoHash* actual = tablaHash[i];
            while (actual != NULL){
                printf(" -> \"%s\"", actual->datosCancion->titulo);
                actual = actual->siguiente;
                contNodos++;                
            }
            printf(" -> NULL\n");
        }
    }
    printf("Estadisticas: %d Canciones en %d indices.\n", contNodos, indicesocupados);
    printf("Factor de Carga: %.2f%%\n", (float)indicesocupados/Tamaño_Tabla * 100);
}