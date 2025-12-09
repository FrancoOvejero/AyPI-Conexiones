#ifndef GRAFO_H_
#define GRAFO_H_

#include <string>
using std::string;

namespace URGGrafo {
	struct Grafo;
	enum TipoGrafo { dirigido, noDirigido };

	/*
	 * Precondicion: -
	 * Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	 * devuelve un grafo dirigido de nombre @nombre al cual se le asocia un identificador unico.
	 * Si @cantidad de vertices es menor que cero devueleve NULL
	 */
	Grafo* CrearGrafoDirigido(string nombre, int cantidadVertices);

	/*
	 * Precondicion: -
	 * Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	 * devuelve un grafo no dirigido de nombre @nombre al cual se le asocia un identificador unico.
	 * Si @cantidad de vertices es menor que cero devuelve NULL
	 */
	Grafo* CrearGrafoNoDirigido(string nombre, int cantidadVertices);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el nombre de @grafo
	 */
	string ObtenerNombre(const Grafo* grafo);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el identificador unico de @grafo
	 */
	string ObtenerIdentificador(const Grafo* grafo);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Si @grafo es un grafo no dirigido, se agrega una relacion de adyacencia conmutativa entre @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @verticeDestino y viceversa).
	 * Si @grafo es un grafo dirigido, se agrega una relacion de adyacencia de @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @vertice destino)
	 * Si @verticeOrigen o @verticeDestino no pertenece al grafo no realiza ninguna accion
	 */
	void Conectar(Grafo* grafo, int verticeOrigen, int verticeDestino);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @verticeOrigen es adyacente a @verticeDestino. Caso contrario devuelve false
	 */
	bool SonAdyacentes(const Grafo* grafo, int verticeOrigen, int verticeDestino);
	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve los vertices en un registro en formato CSV donde cada campo es un vertice
	 */
	string ObtenerVertices(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve las aristas en formato de etiquetas.
	 * El formato de etiquetas para un grafo no dirigido es el siguiente: 1-4 2-3 0-1
	 * Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1)}
	 * El formato de etiquetas para un grafo dirigido es el siguiente: 1-4 2-3 0-1 4-1
	 * Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1), (4,1)}
	 *
	 * Vemos que en ambos casos son las adyacencias separadas por espacio.
	 * Para el caso de los grafos no dirigidos no hay que duplicar las relaciones conmutativas
	 */
	string ObtenerAristas(const Grafo* grafo);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el tipo de @grafo
	 */
	TipoGrafo ObtenerTipo(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @grafo
	 */
	void DestruirGrafo(Grafo* grafo);
}

#endif
