#ifndef EXTRAER_ARCHIVO_H
#define EXTRAER_ARCHIVO_H

#include <iostream>
using namespace std;

// Ayuda a identificar el tipo de procesamiento que se le dará a un texto
enum Identificador {
    PALABRA,
    PAGINA,
    CAPITULO,
    DESCONOCIDO,
    IGNORAR // no representa una palabra válida
};

class ExtraerArchivo {

    private:
        string texto;

        int numeroDeLineas = 0;
    
    public:
        ExtraerArchivo(string texto);
        void procesarTexto();
        pair<string, Identificador> analizarExtracto(string extracto, Identificador identificador);

        int getNumeroLineas();
};

#endif