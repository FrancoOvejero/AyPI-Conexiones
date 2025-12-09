#ifndef CADENA_CARACTERES_H_
#define CADENA_CARACTERES_H_

#include "ResultadoSplit.h"

namespace UndavCadenaCaracteres {
	// Precondicion: @texto es una cadena de caracteres
	// Postcondicion: Devuelve una instancia valida de ResultadoSplit en donde 
	// hay una cadena de caracter por cada campo que esta separado por @separadorCampos
	// en @texto
	ResultadoSplit* Split(const char* texto, char separadorCampos);

	// Precondicion: @resultadoSplit es una instancia valida creada con la primitiva Split
	// Postcondicion: Libera todos los recursos asociados en @resultadoSplit
	void DestruirResultadoSplit(ResultadoSplit* resultadoSplit);
}

#endif