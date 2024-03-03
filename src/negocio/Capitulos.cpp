#include "Capitulos.hpp"
#include "ExtraerArchivo.hpp"
#include "algorithm"

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

void Capitulos::buscarCapituloIndice(string nombre, HashTable<string, string, string> palabrasTabla, vector<string> llavero) {
    vector<string> palabrasEnCapitulo;

    for (string llave: llavero) {
        
       list<tuple<string, string, string>> palabras = palabrasTabla.buscar(llave);

        if (!palabras.empty()) {
            
            for (const auto& trio : palabras) {
                string palabra = get<0>(trio);
                string capitulo = get<2>(trio);

                if (capitulo.find(nombre) != string::npos) {
                    if(std::find(palabrasEnCapitulo.begin(), palabrasEnCapitulo.end(), palabra) == palabrasEnCapitulo.end()) {
                        palabrasEnCapitulo.push_back(palabra);
                    }
                }
            }         
        }
    }
    
    sort(palabrasEnCapitulo.begin(), palabrasEnCapitulo.end());
    
    cout << "Capitulo: " << nombre << endl;
    for (string palabra : palabrasEnCapitulo) {
        cout << palabra << endl;
    }
}

void Capitulos::mostrar() {
    for (CapituloEstructura capitulo : capitulos) {
        cout << "Capitulo: " << capitulo.nombre << " - " << capitulo.paginaInicio << endl;
    }

}