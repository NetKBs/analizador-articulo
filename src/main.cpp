#include <iostream>
#include <ncurses.h>
#include <ostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./presentacion/GUI.h"
#include "./negocio/Documento.hpp"
#include "./presentacion/GUI.h"

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
    
    Documento documento = Documento(articulo);
    documento.procesarTexto();
    documento.procesarDocumento();

    GUI gui(documento);
    gui.showMenu();

    return 0;
}