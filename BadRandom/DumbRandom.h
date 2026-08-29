#ifndef DUMBRANDOM_H
#define DUMBRANDOM_H

#include "Random.h"

struct DumbRandom {
public:
	DumbRandom(int min, int max);
	int Next();

private:
	const int max;
	const int min;
	char* RandomPtr();
};

#endif