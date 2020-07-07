# Root-Finding Methods in C++

A few root/zero finding algorithms written in C++. Methods include the Bisection Method and Secant Method.

**Author:** Michael Wrona | *B.S. Aerospace Engineering*

## How to Use

The algorithms are contained in `findRoots.cpp` and `findRoots.h`. The root-finding algorithms are in a class. An example of how to use the functions can be found in `main.cpp`.

Convergence/solution parameters such as max. # of iterations and tolerance can be changed in the `RootConst` namespace within `findRoots.h`.

## Compilation

The makefile included in the repository will compile the project files and output an executable. To compile and output an executable, simply type the command:

    $ make

To compile and immediately execute the program, type the command:

    $ make run

The console output from `main.c` will look something like:

    BISECTION METHOD
    Solution Results: 
        x = 3.72615
        Iterations: 28
        Tol: 7.45058e-09

    SECANT METHOD
    Solution Results: 
        x = 3.72615
        Iterations: 4
        Tol: 5.27232e-11

If you use code from this repository, I would really appreciate you citing this repo at the top of your code. Always cite your sources!
