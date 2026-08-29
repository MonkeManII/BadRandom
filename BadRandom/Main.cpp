#include "DumbRandom.h"
#include "Random.h"
#include <stdio.h>

int main()
{
    DumbRandom rand = DumbRandom(1, 10);

    for (int i = 0; i < 100; ++i) {
        std::cout << rand.Next() << '\n';
    }

    return 0;
}