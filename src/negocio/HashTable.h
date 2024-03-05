
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple> 
#include <functional> // Para std::hash
#include <map>
#include <set>

using namespace std;

template<typename KeyType, typename SecondValue, typename ExtraValue>
class HashTable {
private:
    static const int TABLE_SIZE = 30000;
  
public:
    vector<list<tuple<KeyType, SecondValue, ExtraValue>>> table;
public:
    HashTable() {
        table.resize(TABLE_SIZE);
    }
    void insert(const KeyType& key, const SecondValue& value, const ExtraValue& extra) {
        int index = hashFunction(key);
        table[index].push_back(make_tuple(key, value, extra));
    }
    // Función para buscar un elemento por clave y devolver la lista completa
    list<tuple<KeyType, SecondValue, ExtraValue>> buscar(const KeyType& key) {
        int index = hashFunction(key);
        return table[index];
    }

    size_t hashFunction(const KeyType& key) {
        return std::hash<KeyType>{}(key) % TABLE_SIZE;
    }

};

#endif // HASHTABLE_H
