#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Player.h"
// 
class HashTable {
    /// player pointer - might change
    Player* table;
    int size;
    int num_of_elements;

public:
    HashTable(int size = 1); //c'tor
    ~HashTable() = default; //d'tor
    HashTable(const HashTable& other) = default; //copy c'tor
    HashTable& operator=(const HashTable& other) = default; //assignment
    int hash_func(int key); //modulo function
    bool reHash(int new_size);
    void clear();
    void clearHashTable();
    bool Insert(Player* info);
    //bool Delete(int key, bool flag);
    bool Find(int key);
    Player* GetPlayer(int key);
    Player* getTable();
    int getNumOfElements() const;
    void setNumOfElements(int new_num);
    int getSize() const;
    void setSize(int new_size);
    void setTable(Player* new_table);
};


#endif //WET2_HASHTABLE_H
