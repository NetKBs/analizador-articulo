#ifndef DOCUMENTO_HPP
#define DOCUMENTO_HPP

#include "Capitulos.hpp"
#include "Indice.h"
#include "ExtraerArchivo.hpp"

#include <iostream> 
using namespace std;

class Documento {

    private:
        string texto;
        int numeroDeLineas, numeroDeCapitulos, numeroDePaginas, numeroPalabrasTotal = 0;
        Indice indice;
        Capitulos capitulos;
        ExtraerArchivo extractor;

    private:
        void procesarTexto();

    public:
        Documento(string texto);
        
        void agregarCapitulos(vector<CapituloEstructura> capitulos);
        void mostrarCapitulos();

        void agregarPalabra(vector<PalabraEstructura> palabras);
        void getIndice();

        // Procesa el documento para poder ser impreso por pantalla
        string procesarDocumento();

        void setNumeroLineas(int numeroDeLineas);
        int getNumeroLineas();
        int getNumeroPaginas();
        int getNumeroDeCapitulos();
        int getNumeroPalabrasTotal();
        

};

#endif