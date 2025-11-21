/*
  Módulo de Procesamiento de Archivos (CSV Parser)
  ------------------------------------------------
  Este bloque de codigo gestiona la carga de datos desde un archivo csv
  La funcion estática 'parse_csv_line' actua como un analizador lexico
  que descompone cada linea de texto utilizando 'strtok' y el delimitador definido, extrayendo
  de forma segura (usando strncpy) los atributos de la cancion como ID, titulo, ruta y género.
  Posteriormente, 'load_data_from_csv' orquesta el proceso: abre el archivo en modo lectura,
  descarta la cabecera y recorre el documento linea por línea; por cada registro validado,
  invoca a la funcion de la lista enlazada (insertEnd) para crear y almacenar el nuevo nodo en memoria.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivo.h"
#include "lista.h"      // Necesario para insertEnd y acceder a 'tail'
#include "arbolavl.h"   // <--- IMPORTANTE: Necesario para insertarAVL y raizAVL

#define DELIMITADOR ";"

//function (estatica para que sea privada de este archivo)
static int parse_csv_line(char *line, char *id, char *titulo, char *ruta, char *genero) {
    char *token;
    int calificacion = -1;
    
    token = strtok(line, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(id, token, 15); id[15] = '\0'; 

    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(titulo, token, 127); titulo[127] = '\0';
    
    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(ruta, token, 511); ruta[511] = '\0';

    token = strtok(NULL, DELIMITADOR);
    if (token == NULL) return -1;
    strncpy(genero, token, 49); genero[49] = '\0';

    token = strtok(NULL, DELIMITADOR); 
    if (token != NULL) {
        calificacion = atoi(token); 
    }
    
    return calificacion;
}

void load_data_from_csv(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo CSV");
        return;
    }

    char line[1024]; 
    int line_count = 0;
    
    // Descartar encabezado
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("Omitiendo encabezado: %s", line);
    } else {
        fclose(file);
        return; 
    }

    // Leer datos
    while (fgets(line, sizeof(line), file)) {
        line_count++;
        
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char id_str[16];
        char titulo_str[128];
        char ruta_str[512];
        char genero_str[50]; 
        int calificacion_val;

        calificacion_val = parse_csv_line(line, id_str, titulo_str, ruta_str, genero_str);

        if (calificacion_val != -1) {
            // 1. Insertar en la Lista Enlazada (Esto ya lo tenías)
            insertEnd(id_str, titulo_str, ruta_str, genero_str, calificacion_val);
            
            // Esta linea de codigo es muy importante ya que nos permite añador los nodos a nuestro arbol AVL
            // Usamos 'tail' porque insertEnd acaba de poner la nueva cancion al final de la lista enlazada
            // Basicamente lo que hacemos es incertar los nodos en nuestro arbol hasta que la la lista deje de ingresar nodos
            // y tail se puede usar ya que es una variable global de IMPORTANTE ENTENDER ESTO!
            if (tail != NULL) {
                 raizAVL = insertarAVL(raizAVL, tail);
            }
        }
    }

    fclose(file);
    printf("\nDatos cargados exitosamente. Total: %d\n", line_count);
}