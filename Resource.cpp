#include "Resource.h"
#include <iostream>

void Food::use() {
    std::cout << "Eating food...\n";
    // Logic to restore hunger goes here
}

void Water::use() {
    std::cout << "Drinking water...\n";
    // Logic to restore thirst goes here
}

void Wood::use() {
    std::cout << "Using wood to build...\n";
    // Logic to use wood for building
}