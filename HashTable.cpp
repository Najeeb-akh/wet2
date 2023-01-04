#include "HashTable.h"


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
    if(table[key%size].getID() == 0)
    {
        return key%size;
    }
    else
    {
        
        int i=0;
        int x = key%size;
        int hash2 = 1 + (key%7);
        int hash_res = (x + i * hash2) % size;

        for(int i = 0; hash_res < this->size && table[hash_res].getID() != 0 ; i++)
        {
            hash_res = (x + i * hash2) % size; 
        }
        return hash_res;
    }
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

    int prev_size = this->size;
    this->size = new_size;

    Player* new_table = new Player[this->size];
    Player* tmp_table = new Player[prev_size];

    tmp_table = table;
    table = new_table;

    Player current_element = Player();
    int hash_res;
    for(int i=0; i < prev_size; i++)
    {
        current_element = table[i];
        if(current_element.getID() != 0)
        {
            hash_res = hash_func(current_element.getID());
            new_table[hash_res] = Player(current_element);
        }
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

 
int HashTable::getNumOfElements() const
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

