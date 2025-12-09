#ifndef DICCIONARIO_H_
#define DICCIONARIO_H_
#include <string>
using std::string;
// clave string(nombre del txt) y valor void*(grafo*) 

namespace UndavDiccionario {
	struct Diccionario;
	// Precondicion: Ninguna
	// Postcondicion: Crear una instancia valida de diccionario que tiene como clave strings y como valor cualquier tipo (void*) 
	Diccionario* CrearDiccionario();

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @diccionario no contine a @clave agrgar el par de elementos @clave y @valor.
	// Si @diccionario contiente @clave reemplaza el valor asociado a esa clave en diccionario por @valor
	void Agregar(Diccionario* diccionario, string clave, void* valor);

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @diccionario contine a @clave quita el par de elementos clave y valor de diccionario.
	// Caso contrario no realiza ninguna accion
	void Quitar(Diccionario* diccionario, string clave);

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @diccionario contine a @clave devuelve el valor asociado a esa @clave. Caso contario devuelve NULL
	void* Obtener(Diccionario* diccionario, string clave);

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @diccionario contine a @clave devuelve true. Caso contario devuelve false
	bool Contiene(const Diccionario* diccionario, string clave);

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Devuelve la cantidad de pares de elementos que hay en el diccionario
	int CantidadElementos(const Diccionario* diccionario);
	
	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Libera todos los recursos asociados a @diccionario
	void DestruirDiccionario(Diccionario* diccionario);
}

#endif