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
    std::vector<std::string> llavero;

private:
    bool buscarPalabraEnLlavero(const std::string& palabra);

public:
    //Nuevo Agregado
    std::map<std::string, std::set<std::string>> busquedaParcial(const std::string& palabra);
    void insertarPalabras(vector<PalabraEstructura> palabras);
    void mostrarIndice();
    void verificarInsertarPalabra(const std::string &palabra);
 
    vector<std::string> getLlavero();
    pair <bool, int> eliminarPalabraIndice(const string &palabra); 
};

#endif // INDICE_H
