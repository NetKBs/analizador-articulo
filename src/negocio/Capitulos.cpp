#include "Capitulos.hpp"

Capitulos::Capitulos() {}

void Capitulos::insertarCapitulos(vector<CapituloEstructura> capitulos) {
   this -> capitulos = capitulos;
}

void Capitulos::mostrar() {
    for (CapituloEstructura capitulo : capitulos) {
        cout << "Capitulo: " << capitulo.nombre << " - " << capitulo.paginaInicio << endl;
    }

}