#ifndef CONJUNTO_CONEXIONES_H_
#define CONJUNTO_CONEXIONES_H_

#include "Conexion.h"

using UndavConexion::Conexion;

//crea un bag que guarda conexion* .evitar duplicados (1-2 == 2-1)

namespace UndavConjuntoConexion {
	struct ConjuntoConexiones;

	// Precondicion: Ninguna
	// Postcondicion: Crea un conjunto vacio donde los items son de tipo Conexion.
	// El conjunto es equivalente a un conjunto de pares no ordenados.
	ConjuntoConexiones* CrearConjuntoVacio();

	// Precondicion: @conjunto e @items son instancias validas
	// Postcondicion: Si @item no existe dentro de @conjunto lo agrega. 
	// Este es un conjunto de pares no ordenados entonces dos items son iguales si:
	// - Son la misma instancia (esto siempre es asi)
	// - Si los valores p y q de @item son iguales (in importar el orden, conmutativamente tambien son iguales)
	void AgregarConexion(ConjuntoConexiones* conjunto, Conexion* item);

	// Precondicion: @conjunto es una instancia valida
	// Postcondicion: Quita una conexion del conjunto (no importa en que posicion esta). Si el conjunto esta vacio devuelve NULL
	Conexion* QuitarConexion(ConjuntoConexiones* conjunto);

	namespace Iterador {
		struct IteradorConjunto;
		IteradorConjunto* Comienzo(ConjuntoConexiones* conjunto);
		Conexion* ObtenerItem(IteradorConjunto* iterador);
		void Siguiente(IteradorConjunto* iterador);
		void DestruirIterador(IteradorConjunto* iterador);
	}

	// Precondicion: Ninguna
	// Postcondicion: Libera todos los recursos asociados de conjunto
	void DestruirConjunto(ConjuntoConexiones* conjunto);
}

#endif