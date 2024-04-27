#include "HashTable.h"
#include <iostream>
#include <algorithm>

HashTable::Entry::Entry() : isActive(false) {}

HashTable::Entry::Entry(std::string key, std::string value) : key(key), isActive(true) {
    values.push_back(value);
}

HashTable::HashTable(int cap) : capacity(cap), size(0), loadFactor(0) {
    table.resize(capacity);
}

int HashTable::hash(const std::string& key) const {
    int hashValue = 0;
    for (char c : key) {
        hashValue = (hashValue * 31 + c) % capacity;
    }
    return hashValue;
}

void HashTable::rehash() {
    int oldCapacity = capacity;
    capacity *= 2;
    std::vector<Entry> oldTable = table;
    table.clear();
    table.resize(capacity);
    size = 0;  

    for (const auto& entry : oldTable) {
        if (entry.isActive) {
            for (const auto& value : entry.values) {
                insert(entry.key, value);
            }
        }
    }
}

bool HashTable::insert(const std::string& key, const std::string& value) {
    if ((float)size / capacity >= maxLoadFactor) {
        rehash();
    }

    int index = hash(key);
    int initialIndex = index;
    do {
        if (!table[index].isActive) {
            table[index] = Entry(key, value);
            size++;
            return true;
        }
        else if (table[index].isActive && table[index].key == key) {
            table[index].values.push_back(value);
            return true;
        }
        index = (index + 1) % capacity;
    } while (index != initialIndex);
    return false;
}

bool HashTable::update(const std::string& key, const std::string& newValue) {
    int index = hash(key);
    int initialIndex = index;
    do {
        if (table[index].isActive && table[index].key == key) {
            table[index].values.clear();
            table[index].values.push_back(newValue);
            return true;
        }
        if (!table[index].isActive && table[index].key.empty()) {
            break;
        }
        index = (index + 1) % capacity;
    } while (index != initialIndex);
    return false;
}

std::vector<std::string> HashTable::search(const std::string& key) {
    int index = hash(key);
    int initialIndex = index;
    do {
        if (table[index].isActive && table[index].key == key) {
            return table[index].values;
        }
        else if (!table[index].isActive && table[index].key.empty()) {
            break;
        }
        index = (index + 1) % capacity;
    } while (index != initialIndex);
    return {};
}

bool HashTable::remove(const std::string& key) {
    int index = hash(key);
    int initialIndex = index;
    do {
        if (table[index].isActive && table[index].key == key) {
            table[index].isActive = false;
            size--;
            return true;
        }
        index = (index + 1) % capacity;
    } while (index != initialIndex);
    return false;
}

void HashTable::printTable() const {
    bool isEmpty = true;
    for (const auto& entry : table) {
        if (entry.isActive) {
            std::cout << "Key: " << entry.key << " - Value: ";
            for (const auto& v : entry.values) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
            isEmpty = false;
        }
    }
    if (isEmpty) {
        std::cout << "Hash table is empty." << std::endl;
    }
}
