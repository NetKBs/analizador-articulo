#include <algorithm>
#include <iostream>
#include <vector>
#include "HashTable.h"
#include "Indice.h"

// Función para buscar una palabra en el vector llavero
bool Indice::buscarPalabraEnLlavero(const string &palabra) {
  return find(llavero.begin(), llavero.end(), palabra) != llavero.end();
}

void Indice::insertarPalabras(vector<PalabraEstructura> palabras) {
	for (const auto &palabra : palabras) {
    verificarInsertarPalabra(palabra.palabra);
		tabla.insert(palabra.palabra, palabra.pagina, palabra.capitulo);
	}
}

// Verificar palabra e insertar en el atributo llavero
void Indice::verificarInsertarPalabra(const string &palabra) {
    if (!buscarPalabraEnLlavero(palabra)) {
        llavero.push_back(palabra);
        sort(llavero.begin(), llavero.end()); // Ordenar el llavero alfabéticamente
    }
}

// Función para eliminar coincidencias parciales de una palabra en la tabla hashing
pair <bool, int> Indice::eliminarPalabraIndice(const string &palabra) {
    int posicion = tabla.hashFunction(palabra);
    list<tuple<string, string, string>> lista = tabla.table[posicion];
    bool seElimino = false;
    int numEliminados = 0;

    for (auto it = lista.begin(); it != lista.end(); ) {
        if ( search(get<0>(*it).begin(), get<0>(*it).end(), palabra.begin(), palabra.end()) != get<0>(*it).end() ) {
            it = lista.erase(it);
            seElimino = true;
            numEliminados++;
        } else {
            ++it;
        }
    }
    
    if (seElimino) {
        tabla.table[posicion] = lista;
        // eliminamos la palabra del llavero
        llavero.erase(remove(llavero.begin(), llavero.end(), palabra), llavero.end());
        return {true, numEliminados};
    }
    return {false, 0};
    
}

pair<bool, map<string, set<string>>>  Indice::busquedaParcial(const string& palabra) {
    vector<string> llavesCoincidentes;
    bool encontrado = false;

    for (const string& llave : llavero) {
        if (llave.find(palabra) != string::npos) {
            llavesCoincidentes.push_back(llave);
        }
    }

    map<string, set<string>> uniqueWordsAndPages;  // Store unique words and pages

    // Recorrer la tabla hash y entrar dentro del listado y checar conincidencias
    for (const string& llave : llavesCoincidentes) {
        list<tuple<string, string, string>> palabras = tabla.buscar(llave);
        for (const auto& tupla : palabras) {
            if (search(get<0>(tupla).begin(), get<0>(tupla).end(), palabra.begin(), palabra.end()) != get<0>(tupla).end()) {
                uniqueWordsAndPages[get<0>(tupla)].insert(get<1>(tupla));  // agregar palabra y pagina al map
                encontrado = true; // si hay palabras encontradas
            }
        }
    }

    return {encontrado, uniqueWordsAndPages};
}

vector <string> Indice::getLlavero() {
    return llavero;
}