#ifndef  R_RNG_H
#define R_RNG_H

#include <random>

namespace r_rng 
{
    void init(uint32_t seed);
    uint16_t rng_dist();
    uint16_t rng_dist_range(uint32_t val1, uint32_t val2);
    double rng_dist_normal(double mean, double stddeviation);
    
    long rng(long val1, long val2 ); // returns random value between val1 and val2
    double rng_float(double val1, double val2 ); // returns random float value between val1 and val2
    bool one_in(int chance); // has one in chance of returning true
    bool x_in_y(double x, double y); // has x in y chance of returning true
    int dice (int number, int sides); // returns the total for a number of dice   
}
#endif