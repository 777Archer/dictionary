/*David Archer
Dictionary*/

#ifndef HASH_DICTIONARY_CPP
#define HASH_DICTIONARY_CPP

#include "HashDictionary.h"


template <class keyType, class itemType>
HashDictionary<keyType, itemType>::HashDictionary(int size)
{
    this->dictionarySize = size;
    this->numberOfEntries = 0;
    this->dictionary = new DictionaryNode<keyType, itemType>*[dictionarySize];
    for (int i = 0; i < dictionarySize; i++)
    {
        this->dictionary[i] = nullptr;
    }
}


template <class keyType, class itemType>
HashDictionary<keyType, itemType>::~HashDictionary()
{
    delete[] dictionary;
}

template <class keyType, class itemType>
bool HashDictionary<keyType, itemType>::isEmpty()
{
    return(!this->numberOfEntries);
}

template <class keyType, class itemType>
int HashDictionary<keyType, itemType>::getDictionarySize()
{
    return this->dictionarySize;
}

template <class keyType, class itemType>
int HashDictionary<keyType, itemType>::getNumberOfItems()
{
    return this->numberOfEntries;
}

template <class keyType, class itemType>
bool HashDictionary<keyType, itemType>::add(keyType key, itemType item)
{
    DictionaryNode<keyType, itemType>* newNode = new DictionaryNode<keyType, itemType>(key, item);
    DictionaryNode<keyType, itemType>* ptr;
    int index = hashEntry(newNode->getKey());

    ptr = this->dictionary[index];

    if (ptr == nullptr)
    {
        dictionary[index] = newNode;
        this->numberOfEntries++;
        return true;
    }
    else
    {
        while (ptr->getNext() != nullptr)
        {
            ptr = ptr->getNext();
        }
        ptr->setNext(newNode);
        this->numberOfEntries++;
    }
    return true;
}

template <class keyType, class itemType>
int HashDictionary<keyType, itemType>::hashEntry(keyType key)
{
    std::hash<keyType> hash_fn;
    std::size_t str_hash = hash_fn(key);
    str_hash = str_hash % this->dictionarySize;

    return str_hash;
}

template <class keyType, class itemType>
bool HashDictionary<keyType, itemType>::remove(keyType key)
{
    int index = hashEntry(key);
    DictionaryNode<keyType, itemType>* nodeptr = nullptr;
    nodeptr = dictionary[index];

    if (nodeptr == nullptr)
        return false;
    else if (key == nodeptr->getKey())
    {
        dictionary[index] = dictionary[index]->getNext();
        this->numberOfEntries--;
        return true;
    }
    else
    {
        while (nodeptr->getNext() != nullptr)
        {
            if (nodeptr->getNext()->getKey() == key)
            {
                nodeptr->setNext(nodeptr->getNext()->getNext());
                this->numberOfEntries--;
                return true;
            }
            nodeptr = nodeptr->getNext();
        }
        return false;
    }
    return false;
}

template <class keyType, class itemType>
bool HashDictionary<keyType, itemType>::contains(keyType key)
{
    int index = hashEntry(key);

    DictionaryNode<keyType, itemType>* nodeptr = nullptr;
    nodeptr = this->dictionary[index];

    if (nodeptr == nullptr)
        return false;

    if (key == nodeptr->getKey())
        return true;

    while (nodeptr->getNext() != nullptr)
    {
        if (nodeptr->getKey() == key)
            return true;

        nodeptr = nodeptr->getNext();
    }

    return false;

}

template <class keyType, class itemType>
itemType HashDictionary<keyType, itemType>::getItem(keyType key)
{
    int index = hashEntry(key);

    DictionaryNode<keyType, itemType>* nodeptr = nullptr;
    nodeptr = this->dictionary[index];

    if (nodeptr == nullptr)
        throw std::logic_error("Item Does not Exist");

    if (key == nodeptr->getKey())
        return nodeptr->getItem();

    while (nodeptr->getNext() != nullptr)
    {
        if (nodeptr->getKey() == key)
            return nodeptr->getItem();

        nodeptr = nodeptr->getNext();
    }
    throw std::logic_error("Item Does not Exist");
}

template <class keyType, class itemType>
void HashDictionary<keyType, itemType>::traverse(void visit(DictionaryNode<keyType, itemType>&))
{
    DictionaryNode<keyType, itemType>* nodeptr = nullptr;
    nodeptr = dictionary[0];

    for (int i = 0; i < this->dictionarySize; i++)
    {
        if (dictionary[i] != nullptr)
        {
            nodeptr = dictionary[i];

            while (nodeptr->getNext() != nullptr)
            {
                nodeptr = nodeptr->getNext();
                visit(*nodeptr);
            }
        }
    }

}

template <class keyType, class itemType>
std::vector<DictionaryNode<keyType, itemType>> HashDictionary<keyType, itemType>::toVector()
{
    DictionaryNode<keyType, itemType>* nodeptr = nullptr;
    std::vector<DictionaryNode<keyType, itemType>> returnVector;

    nodeptr = dictionary[0];

    for (int i = 0; i < this->dictionarySize; i++)
    {
        if (dictionary[i] != nullptr)
        {
            nodeptr = dictionary[i];
            returnVector.push_back(*nodeptr);

            while (nodeptr->getNext() != nullptr)
            {
                nodeptr = nodeptr->getNext();
                returnVector.push_back(*nodeptr);
            }
        }
    }
    return returnVector;
}
#endif