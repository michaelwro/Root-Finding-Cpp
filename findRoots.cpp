// findRoots.cpp
// ----------------------------------------------------------------------------
// Root-finding numerical methods implemented in C++.
//
// Author: Michael Wrona
// Created: 06 July 2020
// ----------------------------------------------------------------------------
/**
 * Methods include the Secant Method and the Bisection Method. This file
 * contains the class attributes/functions. Numerical method pseudocode from:
 * 
 *  Burden, R. L. and Faires, J. D., Numerical Analysis, 9th ed.,
 *      Brooks/Cole, Massachusetts, 2011.
 * 
 */
// ----------------------------------------------------------------------------


#include "findRoots.h"


// ------------------------------------
// public methods
// ------------------------------------

// ----------------------------------------------------------------------------
// FindRoots(double (*userFunct)(double))
// ----------------------------------------------------------------------------
/**
 * Constructs the root-finding class. Checks to see if the function pointer is
 * null.
 * 
 * @param userFunct Function pointer to the function of interest. Make sure 
 *                  it accepts and returns only one double.
 */
// ----------------------------------------------------------------------------
FindRoots::FindRoots(double (*userFunct)(double))
    :funct(userFunct)
{
    // userFunct = funct;  // Store function pointer

    try {
        if (funct == nullptr)
            throw(-1);
    }
    catch(int errNum) {
        std::cerr << "Function returned nullptr. Please pass function pointer." << '\n';
    }
}


// ----------------------------------------------------------------------------
// BisectionMethod(double a, double b)
// ----------------------------------------------------------------------------
/**
 * Compute roots of a function via the Bisection Method. To use this method,
 * the user specifies initial points left (a) and right (b) of the root. See
 * top of file for pseudocode resource.
 * 
 * @param a     Point left of the root.
 * @param b     Point right of the root.
 * @return      Computed root of the function.
 */
// ----------------------------------------------------------------------------
double FindRoots::BisectionMethod(double a, double b)
{
    int iters;
    double tolCheck, fa, fb, p, fp;

    // Evaluate function for initial point
    fa = funct(a);

    for (iters = 0; iters < RootConst::MAX_ITER; iters++)
    {
        p = a + ((b - a) / 2.0);
        fp = funct(p);

        // Chack for convergence
        tolCheck = (b - a) / 2.0;
        if (fp == 0.0 || tolCheck <= RootConst::TOL)
        {
            if (printResults == true)
                PrintResults(p, iters, tolCheck);
            return p;
        }
        
        // Check which way to move - left or right
        if ((fa * fp) > 0.0)
        {
            a = p;
            fa = fp;
        }
        else
            b = p;
    }

    // If the code reaches this point, the method did not converge.
    PrintNoConvergence(iters);
    return -1.0;
}


// ----------------------------------------------------------------------------
// SecantMethod(double p0, double p1)
// ----------------------------------------------------------------------------
/**
 * Compute roots of a function via the Secant Method. To use this method, the
 * user specifies initial points left (p0) and right (p1) of the root. See top
 * of file for pseudocode resource.
 * 
 * @param p0    Point left of the root.
 * @param p1    Point right of the root.
 * @return      Computed root of the function.
 */
// ----------------------------------------------------------------------------
double FindRoots::SecantMethod(double p0, double p1)
{
    int iters;  // Iteration counter
    double tolCheck = 1.0;
    double p, fp0, fp1;  // Evaluate function: f(p0), f(p1)

    fp0 = funct(p0);
    fp1 = funct(p1);
    p = 0.0;
    for (iters = 0; iters < RootConst::MAX_ITER; iters++)
    {
        // Approx. derivative using a secant line
        p = p1 - ((fp1 * (p1 - p0)) / (fp1 - fp0));

        // Check tolerance
        tolCheck = fabs(p - p1);
        if (tolCheck <= RootConst::TOL)
        {
            if (printResults == true)
                PrintResults(p, iters, tolCheck);
            return p;  // p is solution
        }
        
        // Update p0, fp0, p1, fp1
        p0 = p1;
        fp0 = fp1;
        p1 = p;
        fp1 = funct(p);
    }

    // If the code reaches this point, the method did not converge
    PrintNoConvergence(iters);
    return -1;
}


// ----------------------------------------------------------------------------
// SteffensenMethod(double p0)
// ----------------------------------------------------------------------------
/**
 * Compute roots of a function via Steffensen's Method. To use this method, the
 * user specifies an initial point/guess near the root. Note that depending on
 * the function, a divide-by-zero could occur. If so, try a different method.
 * See top of file for pseudocode resource.
 * 
 * @param p0    Point near the root.
 * @return      Computed root of the function.
 */
// ----------------------------------------------------------------------------
double FindRoots::SteffensenMethod(double p0)
{
    double p, p1, p2, tolCheck, denomTerm;

    // Small number to check for a possible divide-by-zero
    double smallNum = 1e-7;

    int iters;
    for (iters = 0; iters < RootConst::MAX_ITER; iters++)
    {
        p1 = funct(p0);
        p2 = funct(p1);
        denomTerm = p2 - (2 * p1) + p0;
        if (fabs(denomTerm) < smallNum)
        {
            std::cout << "WARNING: A divide-by-zero error is likely to occur.";
            std::cout << " Consider using a different method." << "\n";
            return p2;

        }
        
        p = p0 - (pow(p1 - p0, 2.0) / denomTerm);
        
        // Check for convergence
        tolCheck = fabs(p - p0);
        if (tolCheck <= RootConst::TOL)
        {
            PrintResults(p, iters, tolCheck);
            return p;
        }

        // Reset variables
        p0 = p;
    }

    // If the code reaches here, the method did not converge.
    PrintNoConvergence(iters+1);
}


// ------------------------------------
// private methods
// ------------------------------------

// ----------------------------------------------------------------------------
// PrintResults(double sol, int iters, double solnTol)
// ----------------------------------------------------------------------------
/**
 * Print the results to the console.
 * 
 * @param sol       The computed solution/root.
 * @param iters     The number of iterations needed for convergence.
 */
// ----------------------------------------------------------------------------
void FindRoots::PrintResults(double sol, int iters, double solnTol)
{
    std::cout << "Solution Results: " << std::endl;
    std::cout << "    x = " << sol << std::endl;
    std::cout << "    Iterations: " << iters << std::endl;
    std::cout << "    Tol: " << solnTol << std::endl;
}


// ----------------------------------------------------------------------------
// PrintNoConvergence(int iters)
// ----------------------------------------------------------------------------
/**
 * Print an error message if the method did not converce
 * 
 * @param iters     The number of iterations completed.
 */
// ----------------------------------------------------------------------------
void FindRoots::PrintNoConvergence(int iters)
{
    std::cerr << "CONVERGENCE ERROR: ";
    std::cerr << "Method did not converge after " << iters << " iterations.";
    std::cerr << " Consider changing the bounds or initial guesses." << "\n";
}
