#ifndef INDICE_H
#define INDICE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "HashTable.h"
#include "ExtraerArchivo.hpp"

using namespace std;
struct Dato {
    std::string palabra;
    int pagina;
    int capitulo;
};

class Indice {

public:
    HashTable<string, string, string> tabla = HashTable<string, string, string>();

private:
    std::vector<Dato> datos;
    std::vector<std::string> llavero;

private:
    static bool compararPalabras(const Dato& dato1, const Dato& dato2);
    bool buscarPalabraEnLlavero(const std::string& palabra);
    void quickSort(std::vector<Dato>& datos);

public:
    //Nuevo Agregado
    void insertarPalabras(vector<PalabraEstructura> palabras);
    void mostrarIndice();
    
    void agregarDato(const std::string& palabra, int pagina, int capitulo);
    void construirIndice();
    
};

#endif // INDICE_H