#include <algorithm>
#include <iostream>
#include <vector>
#include "HashTable.h"
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

 // Función para buscar ocurrencias parciales de una palabra y devolver las páginas asociadas
   vector<pair<string, string>> Indice::buscarOcurrenciasParciales(const string keyword) {
       vector<pair<string, string>> ocurrencias;

    list<tuple<string, string, string>> lista = tabla.buscar(keyword);

    for (const auto& item : lista) {
        string palabra = get<0>(item);
        string pagina = get<2>(item);

        // Realizar búsqueda parcial utilizando el algoritmo de KMP
        if (palabra.find(keyword) != string::npos) {
            ocurrencias.push_back(make_pair(palabra, pagina));
        }
    }

        return ocurrencias;
    }


vector<std::string> Indice::getLlavero() {
    return llavero;
}

// Función de búsqueda parcial utilizando el algoritmo Boyer-Moore
void Indice::busquedaParcial(const std::string& palabra) {
    std::vector<std::string> llavesCoincidentes;

    for (const std::string& llave : llavero) {
        if (llave.find(palabra) != std::string::npos) {
            llavesCoincidentes.push_back(llave);
        }
    }

    if (llavesCoincidentes.empty()) {
        std::cout << "La palabra '" << palabra << "' no se encontró en el índice." << std::endl;
    } else {
        std::cout << "La palabra '" << palabra << "' se encontró en las siguientes páginas:" << std::endl;
        for (const std::string& llave : llavesCoincidentes) {
            std::list<std::tuple<std::string, std::string, std::string>> palabras = tabla.buscar(llave);
            for (const auto& tupla : palabras) {
                std::cout << "Palabra: " << get<0>(tupla) << " - Página: " << get<1>(tupla) << std::endl;
            }
        }
    }
}


