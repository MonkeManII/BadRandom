#include "DumbRandom.h"
#include "Random.h"
#include <stdio.h>

int main()
{
    DumbRandom rand = DumbRandom(1, 42);
    PseudoRandom r = PseudoRandom(1, 42);

    std::cout << "PsuedoRandom:\n";
    for (int i = 0; i < 100; ++i) {
        std::cout << r.Next() << '\n';
    }
    std::cout << "-----------------------\n";
    std::cout << "DumbRandom:\n";

    for (int i = 0; i < 100; ++i) {
        std::cout << rand.Next() << '\n';
    }

    return 0;
}