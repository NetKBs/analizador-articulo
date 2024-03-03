#include <algorithm>
#include <iostream>
#include <vector>

#include "Indice.h"

// Función para buscar una palabra en el vector llavero
bool Indice::buscarPalabraEnLlavero(const std::string &palabra) {
  return std::find(llavero.begin(), llavero.end(), palabra) != llavero.end();
}


// Nuevo Agregado
void Indice::insertarPalabras(vector<PalabraEstructura> palabras) {
	for (const auto &palabra : palabras) {
    verificarInsertarPalabra(palabra.palabra);
		tabla.insert(palabra.palabra, palabra.pagina, palabra.capitulo);
	}
}

// Verificar palabra e insertar en el atributo llavero
void Indice::verificarInsertarPalabra(const std::string &palabra) {
    if (!buscarPalabraEnLlavero(palabra)) {
        llavero.push_back(palabra);
        std::sort(llavero.begin(), llavero.end()); // Ordenar el llavero alfabéticamente
    }
}


vector<std::string> Indice::getLlavero() {
    return llavero;
}


