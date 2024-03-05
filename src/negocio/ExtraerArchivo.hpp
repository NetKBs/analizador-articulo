#ifndef EXTRAER_ARCHIVO_H
#define EXTRAER_ARCHIVO_H

#include <iostream>
#include <vector>
using namespace std;

// Ayuda a identificar el tipo de procesamiento que se le dará a un texto
enum Identificador {
    PALABRA,
    PAGINA,
    CAPITULO,
    DESCONOCIDO,
    IGNORAR // no representa una palabra válida
};

struct CapituloEstructura{
    string nombre;
    string paginaInicio;
};

struct PalabraEstructura{
    string palabra;
    string pagina;
    string capitulo;
};

struct Contabilizados {
    int numeroDeLineas;
    int numeroDeCapitulos;
    int numeroDePaginas;
    int numeroDePalabrasTotal;
};

struct ExtraccionReturn {
    vector<PalabraEstructura> palabras;
    vector<CapituloEstructura> capitulos;
    Contabilizados contabilizados;
};


class ExtraerArchivo {

    private:
        string texto;
        int numeroDeLineas, numeroDeCapitulos, numeroDePaginas, numeroPalabrasTotal = 0;
    
    public:
        ExtraerArchivo(string texto);
        ExtraccionReturn procesarTexto();
        pair<string, Identificador> analizarExtracto(string extracto, Identificador identificador);
};

#endif