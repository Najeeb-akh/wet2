#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

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


HashTable::HashTable(int size)
{
    num_of_elements = 0;

    if(size > 0)
    {
        this->size = size;
    }
    else
    {
        this->size = 1;
    }
    table = nullptr;
}



void HashTable::clearHashTable()
{
    this->clear();
}


void HashTable::setTable(Player* new_table)
{
    this->table = new_table;
}

 
int HashTable::hash_func(int key)
{
    return (key%size);
}


 
bool HashTable::reHash(int new_size)
{
    if(table == nullptr)
    {
        return false;
    }

    if(new_size < num_of_elements)
    {
        return false; //shouldn't get here
    }

    int prev_size = size;
    size = new_size;

    Player* new_table = new Player[size];
    Player current_element;

    int hash_res;
    for(int i=0; i < prev_size; i++)
    {
        current_element = table[i];
        hash_res = hash_func(current_element.getID());
        new_table[hash_res] = Player(current_element);
        // if(new_table[hash_res].Insert(current_element.getID(), current_element.getID()) == false)
        // {
        //     return false;
        // }
        //current_element = node_ptr->getNext();
    }

    ///might need to destroy the other table
    
    if(prev_size > 1)
    {
        delete [] table;
        table = nullptr;
    }
    else 
    {
        delete table;
        table = nullptr;
    }
    
    table = new_table;
    return true;
}

 
void HashTable::clear()
{
    if(size == 0 || num_of_elements == 0)
    {
        return;
    }

    // for(int i=0; i<size; i++)
    // {        
    //     table[i].clear(); //clears the ith list
    // }

    delete [] table;
    table = nullptr;

    num_of_elements = 0;
    //size stays as it is
}


 
bool HashTable::Insert(Player* player_to_insert)
{
    if (num_of_elements == 0)
    {
        this->table = new Player();
    }

    int hash_res = hash_func(player_to_insert->getID());
    table[hash_res] = Player(*player_to_insert);
    num_of_elements++;
    if(num_of_elements <= size/4)
    {
        return reHash(size/2 +1);
    }
    if(num_of_elements >= size)
    {
        return reHash(size*2 +1);
    }

    return true;
}


 
/*bool HashTable::Delete(int key, bool flag)
{
    if(table == nullptr)
    {
        return false;
    }

    int hash_res = hash_func(key);
    if(table[hash_res].Delete(key, flag) == false)
    {
        return false;
    }
    num_of_elements--;
    if(num_of_elements == 0)
    {
        this->setSize(1);
        delete[] table;
        table = nullptr;
        return true;
    }

    if(num_of_elements <= size/4)
    {
        return reHash(size/2 +1);
    }
    if(num_of_elements >= size)
    {
        return reHash(size*2 +1);
    }

    return true;
}*/


 
bool HashTable::Find(int key)
{
    if(table == nullptr)
    {
        return false;
    }

    int hash_res = hash_func(key);
    if(table[hash_res].getID() != key)
    {
        return false;
    }
    return true;
}


 
Player* HashTable::GetPlayer(int key)
{
    if(table == nullptr)
    {
        return nullptr;
    }

    int hash_res = hash_func(key);
    return &(table[hash_res]);
}


 
Player* HashTable::getTable()
{
    return this->table;
}

 
int HashTable:: getNumOfElements() const
{
    return this->num_of_elements;
}


 
int HashTable::getSize() const
{
    return this->size;
}


 
void HashTable::setNumOfElements(int new_num)
{
    this->num_of_elements = new_num;
}

 
void HashTable::setSize(int new_size)
{
    this->size = new_size;
}


#endif //WET2_HASHTABLE_H
