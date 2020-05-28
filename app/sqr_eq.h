#ifndef SQR_EQ_H
#define SQR_EQ_H

#define NO_SOL 0
#define ONE_SOL 1
#define TWO_SOL 2

typedef struct _solution {
    double x1;
    double x2;
    int sol_count;
} solution;

solution solve_eq(double a, double b, double c);

#endif
