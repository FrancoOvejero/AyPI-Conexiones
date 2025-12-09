#ifndef FACTORY_GRAFOS_H_
#define FACTORY_GRAFOS_H_

#include "Grafo.h"
#include "ConjuntoConexiones.h"

using URGGrafo::Grafo;
using UndavConjuntoConexion::ConjuntoConexiones;


// Recibe ConjuntoConexiones que crea el parser y devuelve un Grafo*
namespace UndavFactoryGrafos {
    Grafo* CrearGrafo(ConjuntoConexiones* conjunto, int cantidadVertices);

    Grafo* CrearBosque(ConjuntoConexiones* conjunto, int cantidadVertices);
}
#endif