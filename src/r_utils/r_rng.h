#ifdef  R_RNG_H
#define R_RNG_H

    long rng(long val1, val2 ); // returns random value between val1 and val2
    double rng_float(double val1, double val2 ); // returns random float value between val1 and val2
    bool one_in(int chance); // has one in chance of returning true
    bool x_in_y(double x, double y); // has x in y chance of returning true
    int dice (int number, int sides); // returns the total for a number of dice:

#endif