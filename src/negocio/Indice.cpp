#include <algorithm>
#include <iostream>
#include <vector>

#include "Indice.h"

// Función para comparar dos palabras durante el ordenamiento
bool Indice::compararPalabras(const Dato &dato1, const Dato &dato2) {
  return dato1.palabra < dato2.palabra;
}

// Función para buscar una palabra en el vector llavero
bool Indice::buscarPalabraEnLlavero(const std::string &palabra) {
  return std::find(llavero.begin(), llavero.end(), palabra) != llavero.end();
}

// Algoritmo de ordenamiento QuickSort
void Indice::quickSort(std::vector<Dato> &datos) {
  if (datos.size() <= 1) {
    return;
  }

  Dato pivote = datos[datos.size() / 2];
  std::vector<Dato> menores;
  std::vector<Dato> iguales;
  std::vector<Dato> mayores;

  for (const auto &dato : datos) {
    if (dato.palabra < pivote.palabra) {
      menores.push_back(dato);
    } else if (dato.palabra == pivote.palabra) {
      iguales.push_back(dato);
    } else {
      mayores.push_back(dato);
    }
  }

  quickSort(menores);
  quickSort(mayores);

  datos.clear();
  datos.insert(datos.end(), menores.begin(), menores.end());
  datos.insert(datos.end(), iguales.begin(), iguales.end());
  datos.insert(datos.end(), mayores.begin(), mayores.end());
}

// Función para agregar un dato al índice
void Indice::agregarDato(const std::string &palabra, int pagina, int capitulo) {
  datos.push_back({palabra, pagina, capitulo});
}

// Función para construir el índice
void Indice::construirIndice() {
  for (const auto &dato : datos) {
    if (!buscarPalabraEnLlavero(dato.palabra)) {
      llavero.push_back(dato.palabra);
    }
  }

  std::sort(llavero.begin(), llavero.end());

  quickSort(datos);
}

// Nuevo Agregado
void Indice::insertarPalabras(vector<PalabraEstructura> palabras) {
	for (const auto &palabra : palabras) {
		tabla.insert(palabra.palabra, palabra.pagina, palabra.capitulo);
	}
}

// Verificar palabra e insertar en el atributo llavero
void Indice::verificarInsertarPalabra(const std::string &palabra) {
    if (!buscarPalabraEnLlavero(palabra)) {
        llavero.push_back(palabra);
        std::sort(llavero.begin(), llavero.end()); // Ordenar el llavero alfabéticamente
    }
}


vector<std::string> Indice::getLlavero() {
    return llavero;
}


