#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <iostream>

struct PseudoRandom {
public:
	PseudoRandom(int min, int max);
	int Next();

private:
	std::random_device device;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> distribution;
};

#endif