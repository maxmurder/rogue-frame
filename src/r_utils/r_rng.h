#ifndef  R_RNG_H
#define R_RNG_H

#include <random>

namespace r_rng 
{
    typedef std::mt19937 R_RNG;

    void init(uint32_t seed); //initilize rng engine
    uint32_t seed(); //return the current seed value
    R_RNG* engine(); // return a pointer to the engine instance

    bool bern(double probability); // Bernoulli distribution.
    uint32_t rng(); // Uniform int distribution.
    uint32_t rng_range(uint32_t val1, uint32_t val2); //Uniform int distribution in range.
    int binomial(int range, double probability); //binomeal distribution.
    double rng_float(double val1, double val2 ); // Uniform float distribution between val1 and val2
    double normal(double mean, double stddeviation); //normal distribution.
    double exponential(double lambda); // exponential distribution.
    

    int dice (int number, int sides); // returns the total for a number of dice   
}
#endif