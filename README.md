# BadRandom: The world's worst random number generator.

## **I WOULD LIKE TO MAKE THE FOLLOWING EXCEEDINGLY CLEAR:**
1. This is a **BAD RANDOM NUMBER GENERATOR!**
2. Under no circumstances should this be used in production code.
3. This is just me messing around with C++ pointers.
4. I am fully aware of how bad the code is. The point of this was just to implement something I thought might be funny. (segfault-based random numbers).

## With that out of the way, what is this?
`BadRandom` is a memory access violation-based random number generator. It does the following to generate a number:
1. Finds an accessible memory location by pseudo-randomly generating pointers until one points to an accessible memory address.
2. Steps the newly-generated pointer forward until it hits an inaccessible address.
3. Returns the number of steps, normalized to fit a given range.

> Please note that this makes use of an incredibly janky compiler-specific hack (bug?) based on [this StackOverflow answer](https://stackoverflow.com/a/918891/26322302)
> to 'catch' and respond to access violations. This is implemented in `DumbRandom.cpp` as the `Guard()` method.
>
> Due to this hack, it may not work on some compilers, systems, builds, etc. Use at your own risk!
