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



// Función para eliminar coincidencias parciales de una palabra en la tabla hashing
pair <bool, int> Indice::eliminarPalabraIndice(const string &palabra) {
    int posicion = tabla.hashFunction(palabra);
    list<tuple<string, string, string>> lista = tabla.table[posicion];
    bool seElimino = false;
    int numEliminados = 0;

    for (auto it = lista.begin(); it != lista.end(); ) {
        if ( std::search(std::get<0>(*it).begin(), std::get<0>(*it).end(), palabra.begin(), palabra.end()) != std::get<0>(*it).end() ) {
            it = lista.erase(it);
            seElimino = true;
            numEliminados++;
        } else {
            ++it;
        }
    }
    
    if (seElimino) {
        tabla.table[posicion] = lista;
        // eliminamos la palabta del llavero
        llavero.erase(std::remove(llavero.begin(), llavero.end(), palabra), llavero.end());
        return {true, numEliminados};
    }
    return {false, 0};
    
}

std::map<std::string, std::set<std::string>> Indice::busquedaParcial(const std::string& palabra) {
    std::vector<std::string> llavesCoincidentes;

    for (const std::string& llave : llavero) {
        if (llave.find(palabra) != std::string::npos) {
            llavesCoincidentes.push_back(llave);
        }
    }

    std::map<std::string, std::set<std::string>> uniqueWordsAndPages;  // Store unique words and pages

    // Recorrer la tabla hash y entrar dentro del listado que contiene cada posición y revisar si las palabras que están dentro
    // de esa lista coinciden con la palabra buscada
    for (const std::string& llave : llavesCoincidentes) {
        list<tuple<std::string, std::string, std::string>> palabras = tabla.buscar(llave);
        for (const auto& tupla : palabras) {
            if (std::search(std::get<0>(tupla).begin(), std::get<0>(tupla).end(), palabra.begin(), palabra.end()) != std::get<0>(tupla).end()) {
                uniqueWordsAndPages[std::get<0>(tupla)].insert(std::get<1>(tupla));  // Add word and page to map
            }
        }
    }

    return uniqueWordsAndPages;
}

vector <string> Indice::getLlavero() {
    return llavero;
}