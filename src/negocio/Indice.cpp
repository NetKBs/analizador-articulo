#include <iostream>
#include <vector>
#include <algorithm>

// Definición de la estructura de datos para almacenar los datos
struct Dato {
    std::string palabra;
    int pagina;
    int capitulo;
};

class Indice {
private:
    std::vector<Dato> datos;
    std::vector<std::string> llavero;

    // Función para comparar dos palabras durante el ordenamiento
    static bool compararPalabras(const Dato& dato1, const Dato& dato2) {
        return dato1.palabra < dato2.palabra;
    }

    // Función para buscar una palabra en el vector llavero
    bool buscarPalabraEnLlavero(const std::string& palabra) {
        return std::find(llavero.begin(), llavero.end(), palabra) != llavero.end();
    }

    // Algoritmo de ordenamiento QuickSort
    void quickSort(std::vector<Dato>& datos) {
        if (datos.size() <= 1) {
            return;
        }

        Dato pivote = datos[datos.size() / 2];
        std::vector<Dato> menores;
        std::vector<Dato> iguales;
        std::vector<Dato> mayores;

        for (const auto& dato : datos) {
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

public:
    // Función para agregar un dato al índice
    void agregarDato(const std::string& palabra, int pagina, int capitulo) {
        datos.push_back({palabra, pagina, capitulo});
    }

    // Función para construir el índice
    void construirIndice() {
        for (const auto& dato : datos) {
            if (!buscarPalabraEnLlavero(dato.palabra)) {
                llavero.push_back(dato.palabra);
            }
        }

        std::sort(llavero.begin(), llavero.end());

        quickSort(datos);
    }

    // Función para mostrar el índice ordenado
    void mostrarIndice() {
        std::cout << "Vector llavero ordenado:" << std::endl;
        for (const auto& palabra : llavero) {
            std::cout << palabra << std::endl;
        }

        std::cout << "\nVector de datos ordenado:" << std::endl;
        for (const auto& dato : datos) {
            std::cout << dato.palabra << " - " << dato.pagina << " - " << dato.capitulo << std::endl;
        }
    }
};
/*
int main() {
    Indice indice;

    // Agregar datos al índice
    indice.agregarDato("hola", 1, 2);
    indice.agregarDato("adios", 3, 4);
    indice.agregarDato("bienvenido", 5, 6);
    indice.agregarDato("bienvenido", 5, 8);

    // Construir e imprimir el índice
    indice.construirIndice();
    indice.mostrarIndice();

    return 0;
}
*/
