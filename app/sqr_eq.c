#include <math.h>
#include "sqr_eq.h"

solution solve_eq(double a, double b, double c) {
    solution res;

    if(a == 0) {
        if(b == 0) {
            res.sol_count = NO_SOL;
            return res;
        } else {
            res.sol_count = ONE_SOL;
            res.x1 = (-1 * c) / b;
            return res;
        }
    }

    double D = pow(b, 2) - 4*a*c;

    if(D < 0.0) {
        res.sol_count = NO_SOL;
    } else if(D == 0.0) {
        res.sol_count = ONE_SOL;
        res.x1 = (-1.0*b) / (2.0*a);
    } else if(D > 0.0) {
        res.sol_count = TWO_SOL;
        res.x1 = ((-1.0*b) - sqrt(D)) / (2.0*a);
        res.x2 = ((-1.0*b) + sqrt(D)) / (2.0*a);
    }

    return res;
}
