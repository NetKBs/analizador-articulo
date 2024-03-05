#ifndef CAPITULOS_HPP
#define CAPITULOS_HPP

#include "HashTable.h"
#include "ExtraerArchivo.hpp"
#include <iostream>
#include <string>

using namespace std;

class Capitulos {

    private:
        vector<CapituloEstructura> capitulos;
    public:
        Capitulos();
        void insertarCapitulos(vector<CapituloEstructura> capitulos);
        CapituloEstructura buscarUnCapitulo(string nombre);
        pair<bool, vector<string>> buscarCapituloIndice(string nombre, HashTable<string, string, string> palabrasTabla, vector<string> llavero);
    
};

#endif