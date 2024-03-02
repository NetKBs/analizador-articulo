#ifndef DOCUMENTO_HPP
#define DOCUMENTO_HPP

#include "Capitulos.hpp"
#include "ExtraerArchivo.hpp"

#include <iostream> 
using namespace std;

class Documento {

    private:
        string texto;
        int numeroDeLineas, numeroDeCapitulos, numeroDePaginas = 0;

        Capitulos capitulos;
        ExtraerArchivo extractor;

    private:
        void procesarTexto();

    public:
        Documento(string texto);
        
        void agregarCapitulos(vector<CapituloEstructura> capitulos);
        void mostrarCapitulos();

        void setNumeroLineas(int numeroDeLineas);
        int getNumeroLineas();
        int getNumeroPaginas();
        int getNumeroDeCapitulos();
        

};

#endif