// SubMenu.h
#ifndef SubMenu_h
#define SubMenu_h

#include <iostream>
#include <map>
#include <ncurses.h>
#include <set>
#include <vector>
#include "../negocio/Documento.hpp"

using namespace std;


class SubMenu {

private:
    void clearScreen();
    void imprimirMarco(string titulo="");

public:
    SubMenu();  // constructor
    ~SubMenu(); // destructor

    void imprimirDocumento(string textoProcesado);
    void imprimirIndicePalabras(vector<map<string, set<string>>> indicePalabras);
    void buscarUnCapitulo(Documento documento);
    void imprimirConScroll(const vector<string>& lines);
    void imprimirEstadisticas(int numeroDeCapitulos, int numeroDeLineas, int numeroDePaginas, int numeroPalabrasTotal, int numeroDePalabrasUnicas);
    void EliminarPalabra(Documento& documento);
    void MostrarPalabras(Documento documento);
};

#endif





