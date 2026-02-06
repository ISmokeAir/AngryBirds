#ifndef OOP_GAMECONTAINER_H
#define OOP_GAMECONTAINER_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
class GameContainer {
private:
    std::vector<T> elements;
    size_t capacity;
    std::string containerName;

public:
    explicit GameContainer(size_t cap, std::string name)
        : capacity(cap), containerName(std::move(name)) {}

    void add(const T& item) {
        if (elements.size() >= capacity) {
            elements.erase(elements.begin());
        }
        elements.push_back(item);
    }

    T& get(int index) {
        if (index < 0 || index >= (int)elements.size()) {
            throw std::out_of_range("Index invalid in GameContainer");
        }
        return elements[index];
    }

    [[nodiscard]] size_t size() const { return elements.size(); }

    [[nodiscard]] bool isEmpty() const { return elements.empty(); }

    void printDetails() const {
        std::cout << "Container [" << containerName << "]: "
                  << elements.size() << "/" << capacity << " elemente.\n";
    }

    auto begin() { return elements.begin(); }
    auto end() { return elements.end(); }
    auto begin() const { return elements.begin(); }
    auto end() const { return elements.end(); }
};

#endif