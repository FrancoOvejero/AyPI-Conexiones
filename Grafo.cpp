#include "Grafo.h"
#include <random>
#include <time.h>
#include <string>
using namespace std;
using std::string;



struct NodoVertice;
struct NodoAdyacente;

struct NodoVertice {
	int vertice;
	NodoVertice* siguienteVertice;
	NodoAdyacente* primerAdyacente;
};

struct NodoAdyacente {
	NodoVertice* verticeDestino;
	NodoAdyacente* siguienteAdyacente;
};

struct URGGrafo::Grafo {
	string identificadorUnico;
	string nombre;
	int cantidadVertices;
	TipoGrafo tipo;
	NodoVertice* primerVertice;
};

NodoVertice* BuscarNodoVertice(const URGGrafo::Grafo* grafo, int vertice);
NodoAdyacente* CrearUltimoNodoAdyacente(NodoVertice* nodoVertice);
NodoVertice* CrearUltimoNodoVertice(int vertice);
void ConectarGrafoDirigido(NodoVertice* verticeOrigen, NodoVertice* verticeDestino);
void ConectarGrafoNoDirigido(NodoVertice* verticeOrigen, NodoVertice* verticeDestino);
NodoAdyacente* ObtenerUltimoNodoAdyacente(NodoVertice* vertice);
string ObtenerAristasDeVertice(NodoVertice* vertice);
void CargarVertices(URGGrafo::Grafo* grafo);
void DestruirNodosAdyacentes(NodoVertice* vertice);
string GenerarIdentificadorUnico();


URGGrafo::Grafo* URGGrafo::CrearGrafoDirigido(string nombre, int cantidadVertices) {
	Grafo* nuevoGrafo = NULL;
	NodoVertice* primerVertice = NULL;
	if (cantidadVertices >= 0) {
		nuevoGrafo = new Grafo;
		nuevoGrafo->nombre = nombre;
		nuevoGrafo->cantidadVertices = cantidadVertices;
		nuevoGrafo->identificadorUnico = GenerarIdentificadorUnico();
		nuevoGrafo->tipo = dirigido;
		nuevoGrafo->primerVertice = primerVertice;
		CargarVertices(nuevoGrafo);
	}
	return nuevoGrafo;
}

URGGrafo::Grafo* URGGrafo::CrearGrafoNoDirigido(string nombre, int cantidadVertices) {
	Grafo* nuevoGrafo = NULL;
	NodoVertice* primerVertice = NULL;
	if (cantidadVertices >= 0) {
		nuevoGrafo = new Grafo;
		nuevoGrafo->nombre = nombre;
		nuevoGrafo->cantidadVertices = cantidadVertices;
		nuevoGrafo->identificadorUnico = GenerarIdentificadorUnico();
		nuevoGrafo->tipo = noDirigido;
		nuevoGrafo->primerVertice = primerVertice;
		CargarVertices(nuevoGrafo);
	}
	return nuevoGrafo;
}

string URGGrafo::ObtenerNombre(const Grafo* grafo) {
	return grafo->nombre;
}

URGGrafo::TipoGrafo URGGrafo::ObtenerTipo(const Grafo* grafo) {
	return grafo->tipo;
}

string URGGrafo::ObtenerIdentificador(const Grafo* grafo) {
	return grafo->identificadorUnico;
}

bool URGGrafo::SonAdyacentes(const Grafo* grafo, int verticeOrigen, int verticeDestino) {
	NodoAdyacente* iterador = BuscarNodoVertice(grafo, verticeOrigen)->primerAdyacente;
	bool encontrado = false;
	while (iterador != NULL && !encontrado) {
		if (iterador->verticeDestino->vertice == verticeDestino) {
			encontrado = true;
		}
	}
	return encontrado;
}

void URGGrafo::Conectar(Grafo* grafo, int verticeOrigen, int verticeDestino) {
	NodoVertice* nodoOrigen = BuscarNodoVertice(grafo, verticeOrigen);
	NodoVertice* nodoDestino = BuscarNodoVertice(grafo, verticeDestino);
	if (nodoOrigen != NULL && nodoDestino != NULL) {
		switch (ObtenerTipo(grafo)) {
		case dirigido:
			ConectarGrafoDirigido(nodoOrigen, nodoDestino);
			break;
		case noDirigido:
			ConectarGrafoNoDirigido(nodoOrigen, nodoDestino);
			break;
		}
	}
}

string URGGrafo::ObtenerVertices(const Grafo* grafo) {
	NodoVertice* iterador = grafo->primerVertice;
	string vertices = "";
	while (iterador != NULL) {
		vertices += to_string(iterador->vertice) + ',';
		iterador = iterador->siguienteVertice;
	}
	return vertices;
}

string URGGrafo::ObtenerAristas(const Grafo* grafo) {
	NodoVertice* iterador = grafo->primerVertice;
	string aristas = "";
	while (iterador != NULL) {
		aristas += ObtenerAristasDeVertice(iterador);
		iterador = iterador->siguienteVertice;
	}
	return aristas;
}

void URGGrafo::DestruirGrafo(Grafo* grafo) {
	NodoVertice* iterador = grafo->primerVertice;
	NodoVertice* nodoABorrar;
	while (iterador != NULL) {
		nodoABorrar = iterador;
		DestruirNodosAdyacentes(iterador);
		iterador = iterador->siguienteVertice;
		delete nodoABorrar;
	}
	delete grafo;
}

// Funciones auxiliares.

NodoVertice* BuscarNodoVertice(const URGGrafo::Grafo* grafo, int vertice) {
	NodoVertice* iterador = grafo->primerVertice;
	NodoVertice* nodoVerticeBuscado = NULL;
	bool encontrado = false;
	while (iterador != NULL && !encontrado) {
		if (iterador->vertice == vertice) {
			encontrado = true;
			nodoVerticeBuscado = iterador;
		}
		else {
			iterador = iterador->siguienteVertice;
		}
	}
	return nodoVerticeBuscado;
}

void ConectarGrafoDirigido(NodoVertice* verticeOrigen, NodoVertice* verticeDestino) {
	NodoAdyacente* nuevoUltimoAdyacente = CrearUltimoNodoAdyacente(verticeDestino);
	NodoAdyacente* ultimoNodoAdyacente = ObtenerUltimoNodoAdyacente(verticeOrigen);
	if (ultimoNodoAdyacente == NULL) {
		verticeOrigen->primerAdyacente = nuevoUltimoAdyacente;
	}
	else {
		ultimoNodoAdyacente->siguienteAdyacente = nuevoUltimoAdyacente;
	}
}

void ConectarGrafoNoDirigido(NodoVertice* nodoOrigen, NodoVertice* nodoDestino) {
	ConectarGrafoDirigido(nodoOrigen, nodoDestino);
	ConectarGrafoDirigido(nodoDestino, nodoOrigen);
}

NodoVertice* CrearUltimoNodoVertice(int vertice) {
	NodoVertice* ultimoNodoVertice = new NodoVertice;
	ultimoNodoVertice->vertice = vertice;
	ultimoNodoVertice->primerAdyacente = NULL;
	ultimoNodoVertice->siguienteVertice = NULL;
	return ultimoNodoVertice;
}

NodoAdyacente* CrearUltimoNodoAdyacente(NodoVertice* nodoVertice) {
	NodoAdyacente* ultimoNodoAdyacente = new NodoAdyacente;
	ultimoNodoAdyacente->verticeDestino = nodoVertice;
	ultimoNodoAdyacente->siguienteAdyacente = NULL;
	return ultimoNodoAdyacente;
}

NodoAdyacente* ObtenerUltimoNodoAdyacente(NodoVertice* vertice) {
	NodoAdyacente* iterador;
	if (vertice->primerAdyacente == NULL) return NULL;
	iterador = vertice->primerAdyacente;
	while (iterador->siguienteAdyacente != NULL) {
		iterador = iterador->siguienteAdyacente;
	}
	return iterador;
}

string ObtenerAristasDeVertice(NodoVertice* vertice) {
	string aristas = "";
	NodoAdyacente* iterador = vertice->primerAdyacente;
	while (iterador != NULL) {
		aristas += to_string(vertice->vertice) + "-";
		aristas += to_string(iterador->verticeDestino->vertice) + " ";
		iterador = iterador->siguienteAdyacente;
	}
	return aristas;
}

void CargarVertices(URGGrafo::Grafo* grafo) {
	NodoVertice* ultimoNodoVertice = CrearUltimoNodoVertice(0);
	grafo->primerVertice = ultimoNodoVertice;
	for (int i = 1; i < grafo->cantidadVertices; ++i) {
		NodoVertice* nuevoUltimoNodoVertice = CrearUltimoNodoVertice(i);
		ultimoNodoVertice->siguienteVertice = nuevoUltimoNodoVertice;
		ultimoNodoVertice = nuevoUltimoNodoVertice;
	}
	ultimoNodoVertice->siguienteVertice = NULL;
}

void DestruirNodosAdyacentes(NodoVertice* vertice) {
	NodoAdyacente* iterador = vertice->primerAdyacente;
	NodoAdyacente* nodoABorrar;
	while (iterador != NULL) {
		nodoABorrar = iterador;
		iterador = iterador->siguienteAdyacente;
		delete nodoABorrar;
	}
}

const int TOPECLAVE = 27;
const int CANTCARACTERES = 36;
unsigned seed = time(NULL);

std::default_random_engine generator(seed);
std::uniform_int_distribution<int> distribution(0, CANTCARACTERES - 1);

string GenerarCaracter(string caracteres, int indice) {
	string caracter;
	if (indice == 8 || indice == 13 || indice == 18) {
		caracter = '-';
	}
	else {
		caracter = caracteres[distribution(generator)];
	}
	return caracter;
}

string GenerarIdentificadorUnico() {
	string caracteres = "abcdefghijklmnopqrstuvwxyz0123456789";
	string identificadorUnico = "";
	for (int indiceCaracteres = 0; indiceCaracteres < TOPECLAVE; ++indiceCaracteres) {
		identificadorUnico += GenerarCaracter(caracteres, indiceCaracteres);
	}
	return identificadorUnico;
}