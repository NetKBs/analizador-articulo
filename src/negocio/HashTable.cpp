#include <iostream>
#include <vector>
#include <list>
#include <tuple> 

using namespace std;

// Definición de la clase de la tabla hash
template<typename KeyType, typename ValueType, typename ExtraType>
class HashTable {
private:
    static const int TABLE_SIZE = 20000; // Tamaño de la tabla hash
    vector<list<tuple<KeyType, ValueType, ExtraType>>> table; // Vector de listas para manejar colisiones

    size_t hashFunction(const KeyType& key) {
        return std::hash<KeyType>{}(key) % TABLE_SIZE;
    }

public:
    // Constructor
    HashTable() {
        table.resize(TABLE_SIZE);
    }

    // Función para insertar un trío clave-valor-extra en la tabla hash
    void insert(const KeyType& key, const ValueType& value, const ExtraType& extra) {
        int index = hashFunction(key);
        table[index].push_back(make_tuple(key, value, extra));
    }

    // Función para mostrar todos los elementos en la tabla hash
    void display() {
        for (const auto& list : table) {
            for (const auto& trio : list) {
                cout << "Clave: " << get<0>(trio) << ", Valor: " << get<1>(trio) << ", Extra: " << get<2>(trio) << endl;
            }
        }
    }
};

/* Ejemplo de uso
int main() {
    HashTable<string, int, int> miTabla;

    // Insertar elementos en la tabla hash
    miTabla.insert("Hola", 10, 44);
    miTabla.insert("Adios", 20, 12);
    miTabla.insert("Palabra", 30, 15);
    miTabla.insert("Tonto", 14, 8);

    // Mostrar todos los elementos en la tabla hash
    cout << "Elementos en la tabla hash:" << endl;
    miTabla.display();

    return 0;
}
*/