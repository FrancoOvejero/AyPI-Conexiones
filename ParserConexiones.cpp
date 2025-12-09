#include "ParserConexiones.h"
#include "ConjuntoConexiones.h"
#include "Conexion.h"
#include "ArchivoTexto.h"
#include "CadenaCaracteres.h"

// Usamos los namespaces de la Entrega 1
using namespace UndavArchivoTexto;
using namespace UndavCadenaCaracteres;
using namespace UndavConexion;
using namespace UndavConjuntoConexion;

namespace UndavParserConexiones {
    int ObtenerCantidadVertices(ResultadoSplit* registros) {
        if (registros != nullptr && registros->cantidadCampos > 0) {
            return ConvertirACifra(registros->campos[0]);
        }
        return 0;
    }

    ConjuntoConexiones* ParsearArchivoConexiones(const char* pathArchivo, int& cantidadVertices) {
        
        char* contenidoArchivoConexiones = ObtenerContenidoLimpio(pathArchivo);
        
        if (contenidoArchivoConexiones == nullptr) {
            cantidadVertices = 0; 
            return CrearConjuntoVacio();
        }

        ConjuntoConexiones* conjunto = CrearConjuntoVacio();

        ResultadoSplit* registrosArchivo = Split(contenidoArchivoConexiones, '\n');
       
        cantidadVertices = ObtenerCantidadVertices(registrosArchivo);

        //iterar sobre los registros y crear las conexiones
        for (int i = 0; i < registrosArchivo->cantidadCampos; ++i) {
            Conexion* nuevaConexion = CrearConexion(registrosArchivo->campos[i]);
            //conexion valida
            if (nuevaConexion != nullptr) {
                AgregarConexion(conjunto, nuevaConexion); //
            }
        }
        //libero memoria
        DestruirResultadoSplit(registrosArchivo); //
        delete[] contenidoArchivoConexiones;

       return conjunto; 
    }
}