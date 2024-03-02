#include "Capitulos.hpp"
#include "ExtraerArchivo.hpp"

Capitulos::Capitulos() {}

void Capitulos::insertarCapitulos(vector<CapituloEstructura> capitulos) {
   this -> capitulos = capitulos;
}

CapituloEstructura Capitulos::buscarUnCapitulo(string nombre) {
    for (CapituloEstructura capitulo : capitulos) {
        if (capitulo.nombre == nombre) {
            return capitulo;
        }
    }
    return CapituloEstructura();
}

void Capitulos::mostrar() {
    for (CapituloEstructura capitulo : capitulos) {
        cout << "Capitulo: " << capitulo.nombre << " - " << capitulo.paginaInicio << endl;
    }

}