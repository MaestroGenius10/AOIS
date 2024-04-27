#include "Menu.h"
#include <iostream>
#include <string>

void Menu::addElement() {
    std::string key, value;
    std::cout << "Enter key: ";
    std::cin >> key;
    std::cout << "Enter value: ";
    std::cin >> value;
    if (ht.insert(key, value)) {
        std::cout << "Element added successfully.\n";
    }
    else {
        std::cout << "Failed to add element.\n";
    }
}

void Menu::findElement() {
    std::string key;
    std::cout << "Enter key: ";
    std::cin >> key;
    auto values = ht.search(key);
    if (!values.empty()) {
        std::cout << "Values: ";
        for (const auto& v : values) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    else {
        std::cout << "No element found for this key.\n";
    }
}

void Menu::updateElement() {
    std::string key, newValue;
    std::cout << "Enter key: ";
    std::cin >> key;
    std::cout << "Enter new value: ";
    std::cin >> newValue;
    if (ht.update(key, newValue)) {
        std::cout << "Element updated successfully.\n";
    }
    else {
        std::cout << "Failed to update element.\n";
    }
}

void Menu::deleteElement() {
    std::string key;
    std::cout << "Enter key: ";
    std::cin >> key;
    if (ht.remove(key)) {
        std::cout << "Element removed successfully.\n";
    }
    else {
        std::cout << "Failed to remove element.\n";
    }
}

void Menu::printAllElements() {
    ht.printTable();
}

void Menu::run() {
    bool done = false;
    int choice;

    while (!done) {
        std::cout << "\nMenu:\n"
            << "1. Create (Add an element)\n"
            << "2. Read (Find elements by key)\n"
            << "3. Update (Change information by key)\n"
            << "4. Delete (Remove an element by key)\n"
            << "5. Print the entire table\n"
            << "6. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addElement();
            break;
        case 2:
            findElement();
            break;
        case 3:
            updateElement();
            break;
        case 4:
            deleteElement();
            break;
        case 5:
            printAllElements();
            break;
        case 6:
            done = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
