#include "Random.h"
#include <random>
#include <iostream>

PseudoRandom::PseudoRandom(int min, int max) : device(), rng(device()), distribution(min, max)
{ }

int PseudoRandom::Next() {
	return distribution(rng);
}
