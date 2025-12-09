#include <string>
using std::string;

#include "Diccionario.h"

namespace UndavDiccionario {

    struct Nodo {
        string clave;
        void* valor;
        Nodo* siguiente;
    };

    struct Diccionario {
        Nodo* PrimerNodo;
        int cantidad;
    };
    
    Diccionario* CrearDiccionario() {
        Diccionario* nuevoDiccionario = new Diccionario; // Corregido a lowerCamelCase
        nuevoDiccionario->PrimerNodo = nullptr;
        nuevoDiccionario->cantidad = 0;
        return nuevoDiccionario;
    }
    
    Nodo *CrearNodo(string clave, void *valor, Diccionario *diccionario)
    {
        Nodo* nuevoNodo = new Nodo{clave, valor, diccionario->PrimerNodo};
        diccionario->PrimerNodo = nuevoNodo;
        diccionario->cantidad++;
        return nuevoNodo;
    }

    void Agregar(Diccionario* diccionario, string clave, void* valor) {
        Nodo* actual = diccionario->PrimerNodo;
        while (actual != nullptr) {
            if (actual->clave == clave) {
                actual->valor = valor;
                return;
            }
            actual = actual->siguiente;
        }
        Nodo *nuevoNodo = CrearNodo(clave, valor, diccionario);
    }
    
    void Quitar(Diccionario* diccionario, string clave) {
        Nodo* actual = diccionario->PrimerNodo;
        Nodo* anterior = nullptr;
        while (actual != nullptr) {
            if (actual->clave == clave) {
                if (anterior == nullptr) {
                    diccionario->PrimerNodo = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente;
                }
                delete actual;
                diccionario->cantidad--;
                return;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
    }
    
    void* Obtener(Diccionario* diccionario, string clave) {
        Nodo* actual = diccionario->PrimerNodo;
        while (actual != nullptr) {
            if (actual->clave == clave) {
                return actual->valor;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    
    bool Contiene(const Diccionario* diccionario, string clave) {
        Nodo* actual = diccionario->PrimerNodo;
        while (actual != nullptr) {
            if (actual->clave == clave) {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }
    
    int CantidadElementos(const Diccionario* diccionario) {
        return diccionario->cantidad;
    }
    
    void DestruirDiccionario(Diccionario* diccionario) {
        Nodo* actual = diccionario->PrimerNodo;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        delete diccionario;
    }
}