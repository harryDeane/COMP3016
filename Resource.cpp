#include "Resource.h"
#include <iostream>

void Food::use() {
    std::cout << "Eating food...\n";
    
}

void Water::use() {
    std::cout << "Drinking water...\n";
  
}

void Wood::use() {
    std::cout << "Using wood to build...\n";
   
}