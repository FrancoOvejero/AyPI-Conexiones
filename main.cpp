#include <iostream>
#include "Grafo.h"
#include "ParserConexiones.h"
#include "FactoryGrafos.h"
#include "ConjuntoConexiones.h"

using namespace std;
using namespace URGGrafo;
using namespace UndavParserConexiones;
using namespace UndavFactoryGrafos;
using namespace UndavConjuntoConexion;

enum TipoComando{ MostrarAyuda, MostrarGrafo, MostrarBosque };

struct Comando {
    TipoComando tipo;
    char* pathArchivo; // Se mantiene char* para compatibilidad con Parser
};

// Prototipo de función auxiliar para comparar cadenas sin usar <cstring>
bool SonCadenasIguales(const char* texto1, const char* texto2);

// Precondicion: @comando es una instancia valida (creada con CrearComando)
// Postcondicion: 
// Si el comando es de tipo MostrarAyuda, debe mostrar el siguiente texto:
// me debe mostrar un texto de ayuda indicando los comandos validos pior ejemplo:
// Usar [TP.exe] [comando] [pathArchivo]
// - Donde los valores posibles de [comando] son: grafo o bosque
// - [pathArchivo] es un path de archivo valido de conexiones en el formato esperado
//
// Si el comando es de tipo MostrarGrafo, debe mostrar el grafo (Parsear el grafo a partir del 
// del archivo que contiene el comando
//
// Si el comando es de tipo MostrarBosque, debe mostrar un bosque de expansion del grafo (Parsear el bosque de expancion a partir del 
// del archivo que contiene el comando)
void Ejecutar(Comando* comando);

// Precondicion: @argv tiene una cantidad de filas igual a @argc 
// Postcondicion:
// - Crea un comando de tipo MostrarGrafo solo si: @argc es igual a 3 argv[1] es igual al comando "grafo" y argv[2] tiene un path de archivo valido
// - Crea un comando de tipo MostrarBosque solo si: @argc es igual a 3, argv[1] es igual al comando "bosque" y argv[3] tiene un path de archivo valido
// - Caso contrario crea un comando de tipo MostrarAyuda 
Comando* CrearComando(int argc, char* argv[]);

// Precondicion: @argv tiene una cantidad de filas igual a @argc 
// Postcondicion: Ejecuta alguno de los comandos validos descriptos en la post condicion de CrearComando
int main(int argc, char* argv[])
{
    Comando* comando = CrearComando(argc, argv);
    Ejecutar(comando);
    delete comando;

    return 0;
}

// Implementación de auxiliar
bool SonCadenasIguales(const char *texto1, const char *texto2)
{
    if (texto1 == nullptr || texto2 == nullptr) return false;
    
    int i = 0;
    while (texto1[i] != '\0' && texto2[i] != '\0') {
        if (texto1[i] != texto2[i]) {
            return false;
        }
        i++;
    }
    return texto1[i] == '\0' && texto2[i] == '\0';
}

Comando* CrearComando(int argc, char* argv[]) {
    Comando* nuevoComando = new Comando;
    nuevoComando->tipo = MostrarAyuda;
    nuevoComando->pathArchivo = nullptr;

    if (argc == 3) {
        char* accion = argv[1];
        char* ruta = argv[2];

        if (SonCadenasIguales(accion, "grafo")) {
            nuevoComando->tipo = MostrarGrafo;
            nuevoComando->pathArchivo = ruta;
        }
        else if (SonCadenasIguales(accion, "bosque")) {
            nuevoComando->tipo = MostrarBosque;
            nuevoComando->pathArchivo = ruta;
        }
    }

    return nuevoComando;
}

void MensajeAyuda() {
    cout << "usar [mi_programa.exe] [comando] [pathArchivo]" << endl;
    cout << "los valores posibles de [comando] son: grafo o bosque" << endl;
    cout << "[pathArchivo] es un path de archivo valido de conexiones en el formato esperado" << endl;
}


void Ejecutar(Comando* comando) {
    if (comando->tipo == MostrarAyuda) {
        MensajeAyuda();
    }
    else {
        int cantidadVertices = 0;
        ConjuntoConexiones* conexiones = ParsearArchivoConexiones(comando->pathArchivo, cantidadVertices);

        if (conexiones != nullptr && cantidadVertices > 0) {
            Grafo* grafo = nullptr;

            if (comando->tipo == MostrarGrafo) {
                grafo = CrearGrafo(conexiones, cantidadVertices);
            }
            else if (comando->tipo == MostrarBosque) {
                grafo = CrearBosque(conexiones, cantidadVertices);
            }

            if (grafo != nullptr) {
                cout << ObtenerAristas(grafo) << endl;
                DestruirGrafo(grafo);
            }
        }
        else {
            cout << "Error: No se pudo procesar el archivo o la cantidad de vertices es invalida." << endl;
        }

        if (conexiones != nullptr) {
            DestruirConjunto(conexiones);
        }
    }
}
