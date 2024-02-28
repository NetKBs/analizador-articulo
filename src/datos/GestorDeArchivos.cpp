#include "GestorDeArchivos.hpp"
#include <fstream>

std::string GestorDeArchivos::leerArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo) {
        return "";
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();

    return buffer.str();
}