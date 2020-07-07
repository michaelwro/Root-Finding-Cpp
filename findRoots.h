// findRoots.h
// ----------------------------------------------------------------------------
// Root-finding numerical methods implemented in C++.
//
// Author: Michael Wrona
//      GitHub: michaelwro | YouTube: MicWro Engr
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

#ifndef FINDROOTS_H
#define FINDROOTS_H


#include <iostream>
#include <cmath>


/**
 * Store constants for root-finding numerical methods.
 * 
 * @param TOL       Solution tolerance, break when met.
 * @param MAX_ITER  Max. number of iterations, break when met/exceeded.
 */
namespace RootConst {
    constexpr double TOL    = 1e-8;
    constexpr int MAX_ITER  = 1000;
}


class FindRoots
{
    public:
        bool printResults = true;  // Print results to console, default true
        FindRoots(double (*userFunct)(double));  // Constructor
        double SecantMethod(double p0, double p1);  // Roots via Secant Method
        double BisectionMethod(double a, double b);  // Roots via Bisection Method
        double SteffensenMethod(double p0);  // Roots via Steffensen's Method

    protected:
    private:
        double (*funct)(double);  // Store pointer to function to find roots of
        void PrintResults(double sol, int iters, double solnTol);  // Print results
        void PrintNoConvergence(int iters);  // Print error message if no convergence
};


#endif  // FINDROOTS_H
