#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <sstream>

using namespace std;

/**
 * Clase GestorDeArchivo para la manipulación con archivos.
 */
class GestorDeArchivos {

    private:
        stringstream buffer;
    public:
          std::string leerArchivo(const std::string& rutaArchivo);
};

#endif