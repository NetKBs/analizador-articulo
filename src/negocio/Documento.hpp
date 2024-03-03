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
        string textoProcesado;
        int numeroDeLineas, numeroDeCapitulos, numeroDePaginas, numeroPalabrasTotal = 0;
        Indice indice;
        Capitulos capitulos;
        ExtraerArchivo extractor;

    private:
        void procesarTexto();
        // Procesa el documento para poder ser impreso por pantalla
        string procesarDocumento();

    public:
        Documento(string texto);

        void getPalabra(string nombre);
        
        void agregarCapitulos(vector<CapituloEstructura> capitulos);
        void mostrarCapitulos();
        vector<string> getCapituloIndice(string nombreCapitulo);

        void agregarPalabra(vector<PalabraEstructura> palabras);
        vector<map<string, set<string>>> getIndice();
        void buscarPalabra(string palabra);

        bool eliminarPalabra(string palabra);

        void setNumeroLineas(int numeroDeLineas);
        int getNumeroLineas();
        int getNumeroPaginas();
        int getNumeroDeCapitulos();
        int getNumeroPalabrasTotal();

        string getTextoProcesado();
        

};

#endif