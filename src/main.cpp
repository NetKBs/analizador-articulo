#include <iostream>
#include <ostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./presentacion/GUI.h"
#include "./negocio/ExtraerArchivo.hpp"

#include "./negocio/Documento.hpp"

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

  

    //ExtraerArchivo ex = ExtraerArchivo(articulo);
    //ex.procesarTexto();
   
    
    Documento documento = Documento(articulo);

    //documento.getPalabra("toda");
   // documento.getCapituloIndice("1");

    //documento.mostrarCapitulos();
    //documento.mostrarIndice();
    //cout << "Capitulos: " << documento.getNumeroDeCapitulos() << endl;
    //cout << "Paginas: " << documento.getNumeroPaginas() << endl;
    //cout << "Lineas: " << documento.getNumeroLineas() << endl;
    //cout << "PalabrasTotal: " << documento.getNumeroPalabrasTotal() << endl;

    GUI gui(documento);
    gui.showMenu();

    return 0;
}