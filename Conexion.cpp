#include "Conexion.h"
#include "CadenaCaracteres.h"

namespace UndavConexion
{
    struct Conexion
    {
        int p;
        int q;
    };

    // convierte una cadena numérica a entero
int ConvertirACifra(const char* texto)
{
    if (texto == 0) return -1;
    int numero = 0;
    int i = 0;
    bool esDigito = false;
    while (texto[i] != '\0') {
        char c = texto[i];
        //si no es digito
        if (c < '0' || c > '9') {
            return -1; 
        }
        esDigito = true;
        numero = numero * 10 + (c - '0');
        i++;
    }
    if (!esDigito) return -1; // cadena vacía
    return numero;
}

    Conexion* CrearConexion(int p, int q)
    {
        Conexion *conexion = new Conexion;
        conexion->p = p;
        conexion->q = q;
        return conexion;
    }

    Conexion* CrearConexion(char *conexionPQ)
    {
        if (conexionPQ == 0)
            return 0;

        ResultadoSplit* partes = UndavCadenaCaracteres::Split(conexionPQ, '-');
        if (partes == 0 || partes->cantidadCampos != 2)
        {
            if (partes)
                UndavCadenaCaracteres::DestruirResultadoSplit(partes);
            return 0;
        }

        int p = ConvertirACifra(partes->campos[0]);
        int q = ConvertirACifra(partes->campos[1]);

        UndavCadenaCaracteres::DestruirResultadoSplit(partes);
        if (p == -1 || q == -1) return 0; // formato inválido
        return CrearConexion(p, q);
    }

    int ObtenerP(const Conexion *conexion)
    {
        return conexion ? conexion->p : 0;
    }

    int ObtenerQ(const Conexion *conexion)
    {
        return conexion ? conexion->q : 0;
    }

    void DestruirConexion(Conexion *conexion)
    {
        delete conexion;
    }
}