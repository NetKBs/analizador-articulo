#ifndef INDICE_H
#define INDICE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "ExtraerArchivo.hpp"

using namespace std;

class Indice {

public:
    HashTable<string, string, string> tabla = HashTable<string, string, string>();

private:
    vector<string> llavero;

private:
    bool buscarPalabraEnLlavero(const string& palabra);

public:

    pair<bool, map<string, set<string>>> busquedaParcial(const string& palabra);
    void insertarPalabras(vector<PalabraEstructura> palabras);
    void mostrarIndice();
    void verificarInsertarPalabra(const string &palabra);
 
    vector<string> getLlavero();
    pair <bool, int> eliminarPalabraIndice(const string &palabra); 
};

#endif // INDICE_H
