#include "Documento.hpp"
#include "ExtraerArchivo.hpp"
#include <sstream>
Documento::Documento(string texto) : extractor(texto) {
    this -> texto = texto;
    procesarTexto();
    this -> textoProcesado = procesarDocumento();
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

vector<map<string, set<string>>> Documento::getIndice() {
  
    vector<string> llavero = this -> indice.getLlavero();
    vector <map<string, set<string>>> indicePalabras; //palabra-paginas

    for (string llave: llavero) {
        
       list<tuple<string, string, string>> palabras = indice.tabla.buscar(llave);

        if (!palabras.empty()) {
            map<string, set<string>> wordMap;
            for (const auto& trio : palabras) {
                string word = get<0>(trio);
                string page = get<1>(trio);
                wordMap[word].insert(page);
            }

            indicePalabras.push_back(wordMap);
        }
    }

    return indicePalabras;
}

void Documento::buscarPalabra(string palabra) {
    vector<pair<string, string>> ocurrencias = this -> indice.buscarOcurrenciasParciales(palabra);
    if(ocurrencias.empty()) {
        cout << "fok" << endl;
    }
    for (const auto& ocurrencia : ocurrencias) {
        cout << ocurrencia.first << " - " << ocurrencia.second << endl;
    }
}

bool Documento::eliminarPalabra(string palabra) {
    this -> indice.eliminarPalabraIndice(palabra);

}

void Documento::agregarCapitulos(vector<CapituloEstructura> capitulos) {
    this -> capitulos.insertarCapitulos(capitulos);
}

void Documento::mostrarCapitulos() {
    this -> capitulos.mostrar();
} 

void Documento::getCapituloIndice(string nombreCapitulo) {
    capitulos.buscarCapituloIndice(nombreCapitulo, indice.tabla, indice.getLlavero());
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

string Documento::getTextoProcesado() {
    return this -> textoProcesado;
}