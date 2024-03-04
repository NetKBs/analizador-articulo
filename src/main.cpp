#include <iostream>
#include <ncurses.h>
#include <ostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./presentacion/GUI.h"
#include "./negocio/ExtraerArchivo.hpp"
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

  

    //ExtraerArchivo ex = ExtraerArchivo(articulo);
    //ex.procesarTexto();
   
    
    Documento documento = Documento(articulo);
    /*std::map<std::string, std::set<std::string>> palabras = documento.buscarPalabra("con");
    // mostrar el listado de palabras que se buscaron:
    for (const auto& pair : palabras) {
        std::cout << pair.first << ": ";
        for (const auto& word : pair.second) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }*/


    //documento.buscarPalabra("cont");
    //documento.getPalabra("toda");
   // documento.getCapituloIndice("1");

    //documento.mostrarCapitulos();
    //documento.mostrarIndice();
    //cout << "Capitulos: " << documento.getNumeroDeCapitulos() << endl;
    /*cout << "Paginas: " << documento.getNumeroPaginas() << endl;
    cout << "Lineas: " << documento.getNumeroLineas() << endl;
    cout << "PalabrasTotal: " << documento.getNumeroPalabrasTotal() << endl;
    cout << "PalabrasUnicas: " << documento.getNumeroPalabrasUnicas() << endl;*/

    //GUI gui(documento);
    //gui.showMenu();

    return 0;
}