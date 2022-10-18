/*David Archer
Dictionary*/

#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include "DictionaryNode.h"
#include <vector>
#include <iostream>
#include <functional>

template <class keyType, class itemType>
class HashDictionary
{
private:
    int dictionarySize;
    DictionaryNode<keyType, itemType>** dictionary;
    int numberOfEntries;
    int hashEntry(keyType);

public:
    HashDictionary(int);
    ~HashDictionary();
    bool isEmpty();
    int getNumberOfItems();
    int getDictionarySize();
    bool add(keyType, itemType);
    bool remove(keyType);
    bool contains(keyType);
    itemType getItem(keyType);
    void traverse(void visit(DictionaryNode<keyType, itemType>&));
    std::vector<DictionaryNode<keyType, itemType>> toVector();
};
#include "HashDictionary.cpp"
#endif

