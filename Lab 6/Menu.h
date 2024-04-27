#pragma once
#include "HashTable.h"
#include <string>

class Menu {
public:
    void run();

private:
    HashTable ht;

    void addElement();
    void findElement();
    void updateElement();
    void deleteElement();
    void printAllElements();
};


