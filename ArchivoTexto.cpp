#include "ArchivoTexto.h"
#include <cstdio>

// en ArchivoTexto.cpp: abrir un archivo desde la ruta dada.
//leer su contenido
//limpiar el contenido (sacar ' ', '\t', '\r') mantener saltos de linea '\n'
//devolver el contenido limpio en char* (con '\0' al final)

namespace UndavArchivoTexto {
    char* ObtenerContenidoLimpio(const char* pathArchivo) {
        //abrir archivo en modo lectura
        FILE* archivo = fopen(pathArchivo, "r"); 
        if (!archivo) return nullptr;
        char textomax[501]; 
        int posicion = 0;
        // fgetc lee un caracter del archivo y avanza el puntero
        int c = fgetc(archivo);
        while (c != EOF && posicion < 500) {
                if (c != ' ' && c != '\t' && c != '\r') {
                textomax[posicion] = c;  //guardo el caracter en el char
                posicion++;
            }
            c = fgetc(archivo); 
        }

        // verifico si el archivo sigue y devuelvo null
        if (c != EOF) {
            fclose(archivo);
            return nullptr;}

        textomax[posicion] = '\0'; //añado \0 al final
        fclose(archivo);
        //creo espacio memoria de puntero a char con el tamaño + /0
        char* resultado = new char[posicion + 1];
        for (int i = 0; i <= posicion; i++) { 
            resultado[i] = textomax[i];
        }
        return resultado;
    }
}


