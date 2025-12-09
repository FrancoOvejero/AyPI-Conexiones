#include "Conexion.h"

using UndavConexion::Conexion;

namespace UndavConjuntoConexion
{
    struct ConjuntoConexiones {
        struct Nodo {
            Conexion* conexion;
            Nodo* siguiente;
        };

        Nodo* primerNodo; 
        int cantidad;
    };
    
    ConjuntoConexiones* CrearConjuntoVacio() {
        ConjuntoConexiones* conjunto = new ConjuntoConexiones;
        conjunto->primerNodo = nullptr;
        conjunto->cantidad = 0;
        return conjunto;
    }
    
    void AgregarConexion(ConjuntoConexiones* conjunto, Conexion* item) {
        
        int p_item = ObtenerP(item);
        int q_item = ObtenerQ(item);
        // Verificar si la conexion ya existe en el conjunto
        ConjuntoConexiones::Nodo* actual = conjunto->primerNodo;
        while (actual != nullptr) {
            Conexion* existente = actual->conexion;
            int p_existente = ObtenerP(existente);
            int q_existente = ObtenerQ(existente);
           if ((p_existente == p_item && q_existente == q_item) ||
                (p_existente == q_item && q_existente == p_item)) {
                DestruirConexion(item);
                return; // La conexion ya existe, no agregar
            }
            actual = actual->siguiente;
        }
        // Agregar la nueva conexion al inicio del conjunto
        ConjuntoConexiones::Nodo* nuevoNodo = new ConjuntoConexiones::Nodo;
        nuevoNodo->conexion = item;
        nuevoNodo->siguiente = conjunto->primerNodo;
        conjunto->primerNodo = nuevoNodo;
        conjunto->cantidad++;
    }
    
    Conexion* QuitarConexion(ConjuntoConexiones* conjunto) {
        if (conjunto->primerNodo == nullptr) {
            return nullptr; // Conjunto vacio
        }
        ConjuntoConexiones::Nodo* nodoARemover = conjunto->primerNodo;
        Conexion* conexion = nodoARemover->conexion;
        conjunto->primerNodo = nodoARemover->siguiente;
        delete nodoARemover;
        conjunto->cantidad--;
        return conexion;
    }
    
    namespace Iterador {
        struct IteradorConjunto {
            ConjuntoConexiones::Nodo* actual;
        };

        IteradorConjunto* Comienzo(ConjuntoConexiones* conjunto) {
            IteradorConjunto* iterador = new IteradorConjunto;
            iterador->actual = conjunto->primerNodo;
            return iterador;
        }

        Conexion* ObtenerItem(IteradorConjunto* iterador) {
            if (iterador->actual == nullptr) {
                return nullptr;
            }
            return iterador->actual->conexion;
        }

        void Siguiente(IteradorConjunto* iterador) {
            if (iterador->actual != nullptr) {
                iterador->actual = iterador->actual->siguiente;
            }
        }

        void DestruirIterador(IteradorConjunto* iterador) {
            delete iterador;
        }
    }
    
    void DestruirConjunto(ConjuntoConexiones* conjunto) {
        ConjuntoConexiones::Nodo* actual = conjunto->primerNodo;
        while (actual != nullptr) {
            ConjuntoConexiones::Nodo* siguiente = actual->siguiente;
            delete actual; // Liberar el nodo
            actual = siguiente;
        }
        delete conjunto;
    }
}