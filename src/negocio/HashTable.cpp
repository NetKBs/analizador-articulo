#include "HashTable.h"

#include <map>
#include <set>


template <typename KeyType, typename SecondValue, typename ExtraValue>
HashTable<KeyType, SecondValue, ExtraValue>::HashTable() {
  table.resize(TABLE_SIZE);
}

template <typename KeyType, typename SecondValue, typename ExtraValue>
size_t HashTable<KeyType, SecondValue, ExtraValue>::hashFunction(const KeyType& key) {
        return std::hash<KeyType>{}(key) % TABLE_SIZE;
}

// Función para insertar un trío clave-valor-extra en la tabla hash
template <typename KeyType, typename SecondValue, typename ExtraValue>
void HashTable<KeyType, SecondValue, ExtraValue>::insert(const KeyType &key, const SecondValue &value, const ExtraValue &extra) {
	int index = hashFunction(key);
	table[index].push_back(make_tuple(key, value, extra));
}

// DISPLAY AJUSTADO PARA MOSTRAR PALABRAS TIPO INDICE (NO VA ACA)
template <typename KeyType, typename SecondValue, typename ExtraValue>
void HashTable<KeyType, SecondValue, ExtraValue>::display() {
  for (const auto& list : table) {
        if (!list.empty()) {
            // Crear un mapa para almacenar la palabra, el número de ocurrenciasy las páginas 
			map<KeyType, pair<int, set<SecondValue>>> wordMap;

            for (const auto& trio : list) {
                KeyType word = get<0>(trio);
                SecondValue page = get<1>(trio);

                // Incrementar el contador de ocurrencias y añadir la página al conjunto de páginas 
				wordMap[word].first++; wordMap[word].second.insert(page);
            }

            // Mostrar la palabra, el número de ocurrencias y las páginas
            for (const auto& item : wordMap) {
                cout << "Palabra: " << item.first << " - Numero de ocurrencias:" << 
				item.second.first << " - Paginas: "; 
				for (const auto& page :item.second.second) { 
					cout << page << " ";
                }
                cout << endl;
            }
        }
    }
}

