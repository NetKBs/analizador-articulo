#include "Documento.hpp"
#include "ExtraerArchivo.hpp"
#include <sstream>
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
    this -> numeroPalabrasTotal = resultados.contabilizados.numeroDePalabrasTotal;
    agregarCapitulos(resultados.capitulos);
    agregarPalabra(resultados.palabras);

}

void Documento::agregarPalabra(vector<PalabraEstructura> palabras) {
    this -> indice.insertarPalabras(palabras);
}

void Documento::getIndice() {
    cout << "hola"<< endl;
    vector<string> llavero = this -> indice.getLlavero();
    for (string llave: llavero) {
        cout << llave << endl;
       list<tuple<string, string, string>> palabras = indice.tabla.buscar(llave);

       for (const auto& tupla : palabras) {
           cout << get<0>(tupla) << " " << get<1>(tupla) << " " << get<2>(tupla) << endl;
       }
    }
}

void Documento::agregarCapitulos(vector<CapituloEstructura> capitulos) {
    this -> capitulos.insertarCapitulos(capitulos);
}

void Documento::mostrarCapitulos() {
    this -> capitulos.mostrar();
} 

string Documento::procesarDocumento() {
    istringstream streamTexto(texto);
    string linea;
    string textoProcesado = "";
    

    while (std::getline(streamTexto, linea)) {
        std::istringstream streamLinea(linea);
        std::string palabra;
        string modelo = "";
        while (streamLinea >> palabra) {
            if (palabra.find("<sub") != string::npos || palabra.find("<pagina") != string::npos) {
                break;
            }
             
            if (palabra.find("<capitulo") != string::npos) {
                size_t inicio = linea.find(' ') + 1;
                size_t fin = linea.find('>', inicio);

                if (inicio != string::npos && fin != string::npos) {
                    texto = linea.substr(inicio, fin - inicio);
                    CapituloEstructura capitulo = capitulos.buscarUnCapitulo(texto);
                    if (capitulo.paginaInicio != "") {
                        modelo = "Capitulo " + texto + " - Página " + capitulo.paginaInicio + "\n";
                        textoProcesado += modelo;
                    }
                    break;
                }   
            
            } else {
                textoProcesado += palabra + " ";
            }
    }
    textoProcesado += "\n";
    
}
return textoProcesado;
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

int Documento::getNumeroPalabrasTotal() {
    return this -> numeroPalabrasTotal;
}