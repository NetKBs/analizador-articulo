#include <iostream>
#include <ostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./GUI/GUI.h"
#include "./negocio/ExtraerArchivo.hpp"

using namespace std;

int main (int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <file_path>\n";
        return 1;
    }

    string articulo = GestorDeArchivos().leerArchivo(argv[1]);
    if (articulo == "") {
        cerr << "No se pudo leer el archivo: " << argv[1] << std::endl;
        return 1;
    }

    ExtraerArchivo ex = ExtraerArchivo(articulo);
    ex.procesarTexto();
    //GUI gui;
    //gui.showMenu();
    
    return 0;
}