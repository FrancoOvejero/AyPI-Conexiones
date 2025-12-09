#ifndef ARCHIVO_TEXTO_H_
#define ARCHIVO_TEXTO_H_

namespace UndavArchivoTexto {
	//Precondicion: @pathArchivo es una cadena de caracteres. El archivo no puede tener mas de 500 caracteres
	//Postcondicion: Si @pathArchivo es una ruta valida, devuelve todo el contenido del archivo en una cadena de caracteres
	// Donde:
	// - No deberia contener ningun espacio en blanco.
	// - El separador de registros es solamente el caracter \n
	// - No hay ningun caracter especial de fin de archivo, solamente el fin de cadena \0
	// Ejemplo: 
	// Para el archivo de texto:
	/*
	* 1-2
	* 2 - 5
	* 
	* 
	*/
	// Se esperaria obtener el siguiente vector: ['1','-','2','\n','2','-','5','\0']. Notar como no se incluyeron los espacios
	// en blanco en la respuesta
	char* ObtenerContenidoLimpio(const char* pathArchivo);
}

#endif