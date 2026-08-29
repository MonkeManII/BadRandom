#include "Random.h"
#include "DumbRandom.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <tchar.h>

typedef void (*SignalHandlerPointer)(int);
static SignalHandlerPointer previousHandler;
static void SignalHandler(int signal)
{
	throw "!Access Violation!";
}

// prevents access violations from being thrown using black magic. might not work depending on compiler :)
static void Guard() { previousHandler = signal(SIGSEGV, SignalHandler); }

void DumbRandom::RandomizePtr() {
	bool succ = false;
	PseudoRandom* rand = new PseudoRandom(0, 255);
	while (!succ) {

		char scratch[sizeof(void*)] = {};
		for (unsigned int i = 0; i < sizeof(void*); ++i) {
			scratch[i] = (char)rand->Next();
		}

		curPtr = (void*)scratch;

		Guard();
		try {
			char _ = *(char*)curPtr;
			succ = true;
		} catch(...) { }
	}
	delete rand;
}

DumbRandom::DumbRandom(int min, int max) : min(min), max(max) {
	RandomizePtr();
	
	// okay, at this point curPtr points to a space in memory
	// that is probably fine to read from.

	// we use that "probably" for its "probability" :)
}

int DumbRandom::Next() {
	int count = 0;

	while (count <= 0) {
		Guard();
		try {
			while (true) {
				// this is where it will error.
				// this is bad design. don't do this in prod code.
				// please.
				++count;
				char _ = *((char*)curPtr + count);
			}
		}
		// this is suboptimal code, buuuuuuuuuuut thats the point.
		catch (...) {
			curPtr = (void*)((char*)curPtr + count);
		}
	}
	RandomizePtr();
	return (count % (max - min)) + min;
}