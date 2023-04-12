#include <iostream>
#include "tuit.h"

int main() {
/*
    Tuit tuit;
    tuit.load("file1.txt");
    std::cout << tuit;
    std::cin.get();
*/

/*
    Tuit tuit;
    std::ifstream in("file1.txt");
    if (!in.is_open()){
        std::cout << "\nNo se pudo abrir el archivo\n";
        std::cin.get();
    }

    in >> tuit;
    std::cout << tuit;
    std::cin.get();
*/

    Tuit tuit1("Juan Perez", "Este es un tuit de prueba");
    tuit1
            .add_element(new Emoji(1, ":)", 1))
            .add_element(new Media(2, "imagen1.png"));

    Tuit tuit2 ("Maria Diaz", "Respuesta a primer tuit");
    tuit2
            .add_element(new Emoji(1, "<3", 1));

    Tuit tuit3 ("Pedro Ramos", "Segunda respuesta del tuit");
    tuit3
            .add_element(new Emoji(1, ":))", 1))
            .add_element(new Poll(2, "Seleccione la opcion",
                                  {"Opcion A",
                                   "Opcion B",
                                   "Opcion C"}, 1, 0, 0));
    tuit1
            .add_reply(tuit2)
            .add_reply(tuit3);

    tuit1.show(std::cout);

    std::cin.get();
}
