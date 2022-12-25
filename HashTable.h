#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "Player.h"
template <class S>
class HashTable {
    /// player pointer - might change
    S** table;
    int size;
    int num_of_elements;

public:
    HashTable(int size = 1); //c'tor
    ~HashTable() = default; //d'tor
    HashTable(const HashTable<S>& other) = default; //copy c'tor
    HashTable<S>& operator=(const HashTable<S>& other) = default; //assignment
    int hash_func(int key); //modulo function
    bool reHash(int new_size);
    void clear();
    void clearHashTable();
    bool Insert(int key, S* info);
    bool Delete(int key, bool flag);
    bool Find(int key);
    S* GetInfoPtr(int key);
    LinkedList<S>* getTable();
    int getNumOfElements() const;
    void setNumOfElements(int new_num);
    int getSize() const;
    void setSize(int new_size);
    void setTable(LinkedList<S>* new_table);
};


template <class S>
HashTable<S>::HashTable(int size)
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


template <class S>
void HashTable<S>::clearHashTable()
{
    this->clear();
}

template <class S>
void HashTable<S>::setTable(S* new_table)
{
    this->table = new_table;
}

template <class S>
int HashTable<S>::hash_func(int key)
{
    return (key%size);
}


template <class S>
bool HashTable<S>::reHash(int new_size)
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

    S** new_table = new S*[size];
    S* node_ptr = nullptr;
    int hash_res;
    for(int i=0; i < prev_size; i++)
    {
        node_ptr = table[i];
        while(node_ptr)
        {
            hash_res = hash_func(node_ptr->getKey());
            if(new_table[hash_res].Insert(node_ptr->getKey(), node_ptr->getInfo()) == false)
            {
                return false;
            }
            node_ptr = node_ptr->getNext();
        }
    }

    for(int i=0; i < prev_size; i++)
    {
        table[i].clearNoDelete();
    }
    
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

template <class S>
void HashTable<S>::clear()
{
    if(size == 0 || num_of_elements == 0)
    {
        return;
    }

    for(int i=0; i<size; i++)
    {        
        table[i].clear(); //clears the ith list
    }

    delete [] table;
    table = nullptr;

    num_of_elements = 0;
    //size stays as it is
}


template <class S>
bool HashTable<S>::Insert(int key, S* info)
{
    if (num_of_elements == 0)
    {
        this->table = new LinkedList<S>();
    }
    int hash_res = hash_func(key);
    if(table[hash_res].Insert(key, info) == false)
    {
        return false;
    }
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


template <class S>
bool HashTable<S>::Delete(int key, bool flag)
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
}


template <class S>
bool HashTable<S>::Find(int key)
{
    if(table == nullptr)
    {
        return false;
    }

    int hash_res = hash_func(key);
    if(table[hash_res].getInfoPtr(key) == nullptr)
    {
        return false;
    }
    return true;
}


template <class S>
S* HashTable<S>::GetInfoPtr(int key)
{
    if(table == nullptr)
    {
        return nullptr;
    }

    int hash_res = hash_func(key);
    return table[hash_res].getInfoPtr(key);
}


template <class S>
LinkedList<S>* HashTable<S>::getTable()
{
    return this->table;
}

template <class S>
int HashTable<S>:: getNumOfElements() const
{
    return this->num_of_elements;
}


template <class S>
int HashTable<S>::getSize() const
{
    return this->size;
}


template <class S>
void HashTable<S>::setNumOfElements(int new_num)
{
    this->num_of_elements = new_num;
}

template <class S>
void HashTable<S>::setSize(int new_size)
{
    this->size = new_size;
}


#endif //WET2_HASHTABLE_H
