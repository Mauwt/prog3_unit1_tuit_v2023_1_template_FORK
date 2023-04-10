#include <iostream>
#include "tuit.h"

int main() {

    Tuit tuit;
    tuit.load("file1.txt");
    std::cout << tuit;
    std::cin.get();

}
