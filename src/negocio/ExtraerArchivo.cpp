#include "ExtraerArchivo.hpp"

#include <cctype>

#include <codecvt>
#include <iostream>

#include <locale>
#include <set>
#include <sstream>

#include <algorithm>


// Para manejar string <-> wstring para temas de utf-8
wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;


ExtraerArchivo::ExtraerArchivo(string texto) {
    this -> texto = texto;
}



pair < string, Identificador > ExtraerArchivo::analizarExtracto(string extracto, Identificador identificador) {
    string texto;

    if (identificador == PAGINA || identificador == CAPITULO) {
        size_t inicio = extracto.find(' ') + 1;
        size_t fin = extracto.find('>', inicio);

        if (inicio != string::npos && fin != string::npos) {
            texto = extracto.substr(inicio, fin - inicio);
            Identificador id = identificador == PAGINA ? PAGINA : CAPITULO;
            return {texto, id};
        }
        return {extracto, DESCONOCIDO};

    }


    if (identificador == PALABRA) {
        if (extracto.empty()) return {extracto,IGNORAR};

        wstring acentos = L"áéíóúÁÉÍÓÚüÜñÑ";
        set<wchar_t> cEspecialesValidosApertura = {L'¡', L'¿',L'('};
        set<wchar_t> cEspecialesValidosCierre = {L'!', L'?', L')'};

        wstring w_extracto = converter.from_bytes(extracto);
        bool esValido = true;

        // Verificar si el texto contiene caracteres no validos
        for (int i = 0; i < w_extracto.size() && esValido; i++) {
            wchar_t c = w_extracto[i];
            bool esCaracterValido = cEspecialesValidosApertura.count(c) || cEspecialesValidosCierre.count(c) || c == L',' || c == L'.' || c == L':';
            if (!iswalpha(c) && !esCaracterValido && acentos.find(c) == wstring::npos) {
                esValido = false;
                break;
            }

            // Verificar si . , : están en medio de la palabra
            if ((c == L',' || c == L'.' || c == L':') && i != w_extracto.size() - 1) {
                esValido = false;
                break;
            }
        }

        if (esValido) {
            wchar_t ultimoCaracter = w_extracto[w_extracto.size() - 1];

            // Remover los . , :
            if (ultimoCaracter == L',' || ultimoCaracter == L'.' || ultimoCaracter ==L':') {
                w_extracto = w_extracto.substr(0, w_extracto.size() - 1);
                if (w_extracto.empty()) esValido = false;
            }

            // Verificar si es un enlistamiento tipo a) b) c)...
            if (ultimoCaracter == L')' && esValido) {
                wstring antesParentesis = w_extracto.substr(0, w_extracto.size()-1);

                if (!all_of(antesParentesis.begin(), antesParentesis.end(), ::isalpha) || antesParentesis.size() < 2) {
                    esValido = false;
                }
            }

            // Manejar los carácteres válidos con apertura y cierre
            if (esValido) {
                for (wchar_t c : cEspecialesValidosApertura) {
                    size_t posApertura = w_extracto.find(c);
                    if (posApertura != wstring::npos) {
                        if (posApertura != 0) {
                            esValido = false;
                        }
                        w_extracto = w_extracto.substr(1);
                    }
                }
            }
           
            if (esValido) {
                for (wchar_t c : cEspecialesValidosCierre) {
                    size_t posCierre = w_extracto.find(c);
                    if (posCierre != wstring::npos) {
                        if (posCierre != extracto.size() - 1) {
                            esValido = false;
                        }
                        w_extracto = w_extracto.substr(0, w_extracto.size() - 1);
                    }
                }
            }
            

            if (w_extracto.empty()) esValido = false;
        }

    return {converter.to_bytes(w_extracto), esValido ? PALABRA : IGNORAR};
}


 return {extracto,DESCONOCIDO};
}

void ExtraerArchivo::procesarTexto() {
    istringstream streamTexto(texto);
    string linea;
    pair < string, Identificador > resultado;
    string paginaActual;
    string capituloActual;

    clock_t inicio = clock();

    while (std::getline(streamTexto, linea)) {
        ++numeroDeLineas; // contabilizamos las líneas

        if (linea.empty()) {
            continue;
        }

        std::istringstream streamLinea(linea);
        std::string palabra;
        while (streamLinea >> palabra) {
            resultado = analizarExtracto(palabra, PALABRA);

            if (palabra.find("<pagina") != string::npos || palabra.find("<capitulo") != string::npos) {
                Identificador id = palabra.find("<pagina") != string::npos ? PAGINA : CAPITULO;
                resultado = analizarExtracto(linea, id);
                if (resultado.second == PAGINA) {
                    paginaActual = resultado.first;
                } else if (resultado.second == CAPITULO) {
                    capituloActual = resultado.first;
                }
            } else if (palabra.find("<sub") != string::npos) {
                break;
            }
            
            if (resultado.second == PALABRA) {
                cout << resultado.first << endl;
            } else { // ignorar
                continue;
            }
        }
    }
    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;
    cout << "Lineas recorridas:" << numeroDeLineas << " Tiempo de ejecucion: "<< tiempo << endl;
}
