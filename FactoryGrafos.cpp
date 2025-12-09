#include "FactoryGrafos.h"

using namespace UndavConjuntoConexion;
using namespace UndavConexion;
using namespace URGGrafo;

namespace UndavFactoryGrafos {
    //inicializa array cada vertice es su propio padre
    void Inicializar(int* padres, int cantidad) {
        for (int i = 0; i < cantidad; ++i) {
            padres[i] = i;
        }
    }

    //busca raiz del conjunto al que pertenece i
    int buscarRaiz(int* padres, int i) {
        while (padres[i] != i) {
            i = padres[i];
        }
        return i;
    }

    bool estanConectados(int* padres, int p, int q) {
        return buscarRaiz(padres, p) == buscarRaiz(padres, q);
    }

    void UnirConjuntos(int* padres, int p, int q) {
        int raizP = buscarRaiz(padres, p);
        int raizQ = buscarRaiz(padres, q);
        padres[raizP] = raizQ;
    }


    Grafo* CrearGrafo(ConjuntoConexiones* conjunto, int cantidadVertices) {
        if (conjunto == nullptr) return nullptr;

        Grafo* grafo = URGGrafo::CrearGrafoNoDirigido("grafo_importado", cantidadVertices);

        // recorrer conexiones y conectar
        Iterador::IteradorConjunto* iter = Iterador::Comienzo(conjunto);

        while (Iterador::ObtenerItem(iter) != nullptr){

            Conexion* conexion = Iterador::ObtenerItem(iter);
            if (conexion != nullptr) {
                int p = ObtenerP(conexion);
                int q = ObtenerQ(conexion);

                if (p >= 0 && p < cantidadVertices && q >= 0 && q < cantidadVertices) {
                    URGGrafo::Conectar(grafo, p, q);
                }
                Iterador::Siguiente(iter);
            }
        }

        Iterador::DestruirIterador(iter);
        return grafo;
    }


    Grafo* CrearBosque(ConjuntoConexiones* conjunto, int cantidadVertices) {
        if (conjunto == nullptr) return nullptr;
        int* padres = new int[cantidadVertices];
        Inicializar(padres, cantidadVertices);

        Grafo* grafo = URGGrafo::CrearGrafoNoDirigido("bosque_expansion", cantidadVertices);

        // recorrer conexiones y conectar
        Iterador::IteradorConjunto* iter = Iterador::Comienzo(conjunto);

        while (Iterador::ObtenerItem(iter) != nullptr){

            Conexion* conexion = Iterador::ObtenerItem(iter);
            if (conexion != nullptr) {
                int p = ObtenerP(conexion);
                int q = ObtenerQ(conexion);

                if (p >= 0 && p < cantidadVertices && q >= 0 && q < cantidadVertices) {

                    if(!estanConectados(padres, p,q)){
                        UnirConjuntos(padres, p,q);
                        URGGrafo::Conectar(grafo, p, q);
                    }
                    
                }
                Iterador::Siguiente(iter);
            }
        }

        Iterador::DestruirIterador(iter);
        delete [] padres;
        return grafo;
    }
}
