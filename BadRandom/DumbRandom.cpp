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
static PseudoRandom* random = nullptr;

// prevents access violations from being thrown using black magic. might not work depending on compiler :)
static void Guard() { previousHandler = signal(SIGSEGV, SignalHandler); }
static void UnGuard() { previousHandler = signal(SIGSEGV, SIG_DFL); }

char* DumbRandom::RandomPtr() {
	if (random == nullptr) random = new PseudoRandom(0, 255);

	bool succ = false;
	char* r = nullptr;
	while (!succ) {
		unsigned char scratch[sizeof(void*)] = {};
		for (unsigned int i = 0; i < sizeof(void*); ++i) {
			scratch[i] = (unsigned char)random->Next();
		}

		r = *(char**)scratch;

		Guard();
		try {
			char _ = *r;
			succ = true;
		} catch(...) { }
		UnGuard();
	}
	return r;
}

DumbRandom::DumbRandom(int min, int max) : min(min), max(max) { }

int DumbRandom::Next() {
	int count = 0;

	char* ptr = RandomPtr();

	Guard();
	while (true) {
		try {
			while (true) {
				// this is where it will error.
				// this is bad design. don't do this in prod code.
				// please.
				++count;
				char _ = *(ptr + count);
			}
		}
		// this is suboptimal code, buuuuuuuuuuut thats the point.
		catch (...) { if (count > 0) break; }
	}

	UnGuard();
	
	return (count % (max - min)) + min;
}