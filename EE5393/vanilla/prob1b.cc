// Problem 1b: Stochastic simulation of chemical reaction network
// Starting from [9, 8, 7], run 7 steps, compute mean and variance of X1, X2, X3
//
// Reactions:
//   R1: 2X1 + X2 -> 4X3   k=1
//   R2: X1 + 2X3 -> 3X2   k=2
//   R3: X2 + X3  -> 2X1   k=3

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

// Binomial coefficient C(n, k)
unsigned choose(unsigned n, unsigned k) {
    if (n < k) return 0;
    unsigned result = 1;
    for (unsigned i = 0; i < k; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

int main() {

    srand(time(NULL));

    const int TRIALS = 100000;
    const int STEPS  = 7;

    // accumulators for mean and variance
    double sum1 = 0, sum2 = 0, sum3 = 0;
    double sum1sq = 0, sum2sq = 0, sum3sq = 0;

    for (int n = 0; n < TRIALS; n++) {

        // initial state
        int x1 = 9, x2 = 8, x3 = 7;

        for (int step = 0; step < STEPS; step++) {

            // compute propensities
            double a1 = 1.0 * choose(x1, 2) * choose(x2, 1); // R1
            double a2 = 2.0 * choose(x1, 1) * choose(x3, 2); // R2
            double a3 = 3.0 * choose(x2, 1) * choose(x3, 1); // R3
            double A  = a1 + a2 + a3;

            if (A == 0) break; // no reactions possible

            // pick a reaction weighted by propensity
            double r = (rand() / (double)RAND_MAX) * A;

            if (r < a1) {
                // R1: 2X1 + X2 -> 4X3
                x1 -= 2; x2 -= 1; x3 += 4;
            } else if (r < a1 + a2) {
                // R2: X1 + 2X3 -> 3X2
                x1 -= 1; x2 += 3; x3 -= 2;
            } else {
                // R3: X2 + X3 -> 2X1
                x1 += 2; x2 -= 1; x3 -= 1;
            }
        }

        // accumulate for mean and variance
        sum1   += x1;     sum1sq += (double)x1 * x1;
        sum2   += x2;     sum2sq += (double)x2 * x2;
        sum3   += x3;     sum3sq += (double)x3 * x3;
    }

    // compute mean and variance: Var(X) = E[X^2] - E[X]^2
    double mean1 = sum1 / TRIALS;
    double mean2 = sum2 / TRIALS;
    double mean3 = sum3 / TRIALS;
    double var1  = (sum1sq / TRIALS) - mean1 * mean1;
    double var2  = (sum2sq / TRIALS) - mean2 * mean2;
    double var3  = (sum3sq / TRIALS) - mean3 * mean3;

    cout << "Results after 7 steps from [9, 8, 7] over " << TRIALS << " trials:" << endl;
    cout << endl;
    cout << "X1:  mean = " << mean1 << ",  variance = " << var1 << endl;
    cout << "X2:  mean = " << mean2 << ",  variance = " << var2 << endl;
    cout << "X3:  mean = " << mean3 << ",  variance = " << var3 << endl;

    return 0;
}
