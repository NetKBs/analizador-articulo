#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple> 
#include <functional> // Para std::hash

using namespace std;

template<typename KeyType, typename ValueType, typename ExtraType>
class HashTable {
private:
    static const int TABLE_SIZE = 20000;
    vector<list<tuple<KeyType, ValueType, ExtraType>>> table;

    size_t hashFunction(const KeyType& key);

public:
    HashTable();
    void insert(const KeyType& key, const ValueType& value, const ExtraType& extra);
    void display();
};


#endif // HASHTABLE_H
