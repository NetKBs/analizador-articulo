#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <tuple> 
#include <functional> // Para std::hash

using namespace std;

template<typename KeyType, typename SecondValue, typename ExtraValue>
class HashTable {
private:
    static const int TABLE_SIZE = 30000;
    vector<list<tuple<KeyType, SecondValue, ExtraValue>>> table;

    size_t hashFunction(const KeyType& key);

public:
    HashTable();
    void insert(const KeyType& key, const SecondValue& value, const ExtraValue& extra);
    void display();
};


#endif // HASHTABLE_H
