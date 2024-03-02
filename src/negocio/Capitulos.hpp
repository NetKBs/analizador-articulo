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
        
        void mostrar();
};

#endif