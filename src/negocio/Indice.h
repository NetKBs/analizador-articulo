#ifndef INDICE_H
#define INDICE_H

#include <iostream>
#include <vector>
#include <algorithm>

struct Dato {
    std::string palabra;
    int pagina;
    int capitulo;
};

class Indice {
private:
    std::vector<Dato> datos;
    std::vector<std::string> llavero;

    static bool compararPalabras(const Dato& dato1, const Dato& dato2);
    bool buscarPalabra(const std::string& palabra);
    void quickSort(std::vector<Dato>& datos);

public:
    void agregarDato(const std::string& palabra, int pagina, int capitulo);
    void construirIndice();
    void mostrarIndice();
};

#endif // INDICE_H
