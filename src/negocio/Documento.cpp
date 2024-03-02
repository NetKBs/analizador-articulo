#include "Documento.hpp"
#include "ExtraerArchivo.hpp"

Documento::Documento(string texto) : extractor(texto) {
    this -> texto = texto;
    procesarTexto();
}

void Documento::procesarTexto() {
    ExtraccionReturn resultados = this -> extractor.procesarTexto();
    // Distribuimos datos
    this -> numeroDeLineas = resultados.contabilizados.numeroDeLineas;
    this -> numeroDePaginas = resultados.contabilizados.numeroDePaginas;
    this -> numeroDeCapitulos = resultados.contabilizados.numeroDeCapitulos;

    agregarCapitulos(resultados.capitulos);
    agregarPalabra(resultados.palabras);

}

void Documento::agregarPalabra(vector<PalabraEstructura> palabras) {
    this -> indice.insertarPalabras(palabras);
}

void Documento::mostrarIndice() {
    this -> indice.mostrarIndice();
}

void Documento::agregarCapitulos(vector<CapituloEstructura> capitulos) {
    this -> capitulos.insertarCapitulos(capitulos);
}

void Documento::mostrarCapitulos() {
    this -> capitulos.mostrar();
} 

int Documento::getNumeroDeCapitulos() {
    return this -> numeroDeCapitulos;
}

int Documento::getNumeroPaginas() {
    return this -> numeroDePaginas;
}

int Documento::getNumeroLineas() {
    return this -> numeroDeLineas;
}
