#pragma once
#include <vector>
#include <string>

class HashTable {
private:
    struct Entry {
        std::string key;
        std::vector<std::string> values;
        bool isActive;

        Entry();
        Entry(std::string key, std::string value);
    };

    std::vector<Entry> table;
    int capacity;
    int size;
    float loadFactor;
    const float maxLoadFactor = 0.75;

    int hash(const std::string& key) const;
    void rehash();

public:
    HashTable(int cap = 20);
    bool insert(const std::string& key, const std::string& value);
    bool update(const std::string& key, const std::string& newValue);
    std::vector<std::string> search(const std::string& key);
    bool remove(const std::string& key);
    void printTable() const;
};
