// en CadenaCaracteres.cpp: Split y DestruirResultadoSplit
//destruirResultadoSplit: libera todas los char* 
#include "CadenaCaracteres.h"
#include "ResultadoSplit.h"


namespace UndavCadenaCaracteres {
    // Verifica si un caracter es un separador.
    bool EsSeparador(char c, char separador) {
        return c == separador;
    }
    
    // es campo si el caracter actual no es separador y el anterior si.
    bool EsInicioCampo(char c, char anterior, char separador) {
        return !EsSeparador(c, separador) && EsSeparador(anterior, separador);
    }

    // contar cuantos campos 
    int ContarCampos(const char* texto, char separador) {
        if (!texto) return 0;
        int cantidad = 0;
        bool flag = false;
        char anterior = separador;        

        //recorro el texto hasta \0 y comparo con el separador 
        for (int i = 0; texto[i] != '\0'; i++) {
            if (EsInicioCampo(texto[i], anterior, separador)) {
                cantidad++;
            }
            anterior = texto[i];
        }
        return cantidad;
    }

    //split: recibe un texto y un separador, devuelve la cantidad de campos
    // y un arreglo de char* cada campo en memoria dinamica
	ResultadoSplit* Split(const char* texto, char separadorCampos){
        if (!texto) return nullptr;
        int cantidad = ContarCampos(texto,separadorCampos);
        //creo espacio en memoria 
        ResultadoSplit* resultado = new ResultadoSplit;
        resultado->cantidadCampos = cantidad;
        resultado->campos = new char*[cantidad];

        int i = 0;
        int IndexCampoActual = 0; // índice del campo que creo
        int inicio = 0; // posición inicio de IndexCampoActual

         // Recorremos el texto para separar campos
        while (texto[i] != '\0') {

            if (texto[i] == separadorCampos){
            //si el anterior era numero
                if (i > inicio){

                    int longitud = i - inicio;
                    char* campo = new char[longitud + 1];
                    for (int j = 0; j < longitud; j++){
                    campo[j] = texto[inicio + j];
                    }
                    campo[longitud] = '\0';
                    resultado->campos[IndexCampoActual++] = campo;
                }
                inicio = i + 1;
            }
            i++;
        }
        // Es para crear el campo cuando termina el texto y no por un \n
        if (i > inicio){
            int longitud = i - inicio;
            char *campo = new char[longitud + 1];
            for (int j = 0; j < longitud; ++j){
                campo[j] = texto[inicio + j];
            }
            campo[longitud] = '\0';
            resultado->campos[IndexCampoActual++] = campo;
        }
        return resultado;
    }
    
    void DestruirResultadoSplit(ResultadoSplit *resultadoSplit)
    { // liberar campo individual, array y estructura
        if (!resultadoSplit) return;
        for (int i = 0; i < resultadoSplit->cantidadCampos; i++){
            delete[] resultadoSplit->campos[i];
        }
        delete[] resultadoSplit->campos;
        delete resultadoSplit;
    }
}