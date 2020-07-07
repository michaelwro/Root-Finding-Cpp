// main.cpp
// ----------------------------------------------------------------------------
// Root-finding numerical methods implemented in C++.
//
// Author: Michael Wrona
// Created: 06 July 2020
// ----------------------------------------------------------------------------
/**
 * Methods include the Secant Method and the Bisection Method. Numerical 
 * method pseudocode from:
 * 
 *  Burden, R. L. and Faires, J. D., Numerical Analysis, 9th ed.,
 *      Brooks/Cole, Massachusetts, 2011.
 */
// ----------------------------------------------------------------------------


#include "findRoots.h"

/**
 * The function of interest, to compute roots of.
 * 
 * @param x     Point to evaluate the function at.
 * @return      Function evaluation, f(x).
 */
double myFunction(double x)
{
    return log(x) - (2.5 * x) + 8.0f;
}


int main(int argc, char *argv[])
{
    // Define variables here
    double solnBisect, solnSecant;

    /** 
     * Define class, contains root-finging algorithms. In order to use the
     * functions, we must first pass the function pointer to the constructor.
     * We can also choose whether or not to print the results to the
     * console with the 'printResults' variable. This is true by default.
     */
    FindRoots CalcRoots(myFunction);  // Create object, pass function pointer
    // CalcRoots.printResults = true;  // Default true, change to false if desired

    /**
     * Calculate root via Bisection Method.
     * For the Bisection Method, we must define an upper and lower bound where
     * we believe the root is.
     */
    std::cout << "BISECTION METHOD:" << std::endl;
    double lowBd = 2.0;  // Define left/right bounds
    double upBd = 6.0;
    solnBisect = CalcRoots.BisectionMethod(lowBd, upBd);
    std::cout << "\n";

    /**
     * Calculate root via the Secant Method.
     * Just like the Biesection Method, we must define an upper and lower 
     * bound where we believe the root is.
     */
    std::cout << "SECANT METHOD:" << std::endl;
    solnSecant = CalcRoots.SecantMethod(lowBd, upBd);
    std::cout << "\n";
    return 0;
}





