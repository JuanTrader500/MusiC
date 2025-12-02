# 🎵 MusiC - Proyecto de Estructura de Datos

Bienvenido al repositorio oficial de **MusiC**. Este es un proyecto desarrollado prinsipal mente en **C** como trabajo final para la materia de Estructura de Datos. El objetivo es simular un reproductor o gestor de música utilizando estructuras de datos avanzadas para el manejo eficiente de la información.

## Descripción

MusiC es una aplicación de consola que permite gestionar listas de reproducción y canciones. El proyecto demuestra la implementación práctica de algoritmos y estructuras de datos para organizar, buscar y reproducir archivos de audio.

### Características Principales
* **Gestión de Canciones:** Agregar, eliminar y buscar canciones.
* **Listas de Reproducción:** Creación y manejo de playlists personalizadas.
* **Estructuras de Datos:** Implementación de Listas circulares doble mente enlazadas, arboles AVL y tablas Hash.
* **Interfaz de Consola:** Menús interactivos y fáciles de usar.

##  Tecnologías Utilizadas

* **Lenguaje:** C y C++
* **IDE Recomendado:** Dev-C++ 
* **Sistema Operativo:** Windows

##  Estructura del Proyecto

El código está organizado de forma modular, separando la lógica de las estructuras de datos, la interfaz y la gestión de archivos.

### Archivos Principales
* **`Main.cpp`**: Punto de entrada de la aplicación. Contiene el menú principal (`switch`) y la lógica de control del flujo del programa.
* **`Project1.dev`**: Archivo de configuración del proyecto para Dev-C++.

### Módulos y Componentes
El proyecto se divide en módulos, cada uno con su archivo de cabecera (`.h`) y su implementación (`.cpp`):

* **Audio (`audio.h` / `ImplementacionAudio.cpp`)**:
    * Encargado de la reproducción de música e interacción con los botones/controles.
* **Listas (`lista.h` / `ImplementacionLista.cpp`)**:
    * Implementación de la Lista Circular para el manejo de la cola de reproducción.
* **Árbol AVL (`arbolavl.h` / `ImplementacionAVL.cpp`)**:
    * Estructura de árbol binario de búsqueda equilibrado (AVL) para búsquedas rápidas por título.
* **Recomendador (`recomendador.h` / `ImplementacionRecomendador.cpp`)**:
    * Lógica para el sistema de recomendaciones de canciones.
* **Interfaz (`interfaz.h` / `ImplementacionInterfaz.cpp`)**:
    * Manejo de los menús visuales y la estética de la consola.
* **Archivos (`archivo.h` / `ImplementacionArchivo.cpp`)**:
    * Gestión de lectura y escritura de datos para guardar/cargar las canciones y playlists.

---
## Instalación y Ejecución

### Prerrequisitos
Necesitas tener instalado un compilador de C++ o el IDE **Dev-C++**.

### Pasos para ejecutar

1.  **Clonar el repositorio:**
    ```bash
    git clone [https://github.com/JuanTrader500/MusiC.git]
    ```
2.  **Abrir el proyecto:**
    * Navega a la carpeta y abre el archivo `.dev` con Dev-C++.
3.  **Compilar y Correr:**
    * *Nota:* revisa la carpeta `Tutorial` para que puedas importar las librerias necesarias de la forma correcta antes de ejecutar el programa.
    *  Presiona `F11` en Dev-C++ para compilar y ejecutar.

## Tutorial de Uso

Como el grabador de pantalla de Windows no capturó los menús desplegables de Dev-C++ durante la demo, he incluido una carpeta llamada **`Tutorial`**.
> **Por favor revisa las imágenes en esa carpeta para entender mejor cómo configurar y ejecutar el proyecto correctamente.**

##  Contribuciones

Este es un proyecto académico, pero las sugerencias son bienvenidas. Si deseas mejorar el código:
1.  Haz un Fork del proyecto.
2.  Crea una rama con tu nueva funcionalidad (`git checkout -b feature/AmazingFeature`).
3.  Haz Commit de tus cambios (`git commit -m 'Add some AmazingFeature'`).
4.  Haz Push a la rama (`git push origin feature/AmazingFeature`).
5.  Abre un Pull Request (Like Camilo :V)
