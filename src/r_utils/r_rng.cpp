#include <random>
#include "r_rng.h"

namespace r_rng {
    uint32_t _seed;  
    r_rng::R_RNG inst;
    std::uniform_int_distribution<uint32_t> uint_dist;
}

void r_rng::init(uint32_t seed)
{
    r_rng::_seed = seed;
    srand(_seed);
    r_rng::inst.seed(r_rng::_seed);
}

r_rng::R_RNG* r_rng::engine()
{
    return &r_rng::inst;
}

uint32_t r_rng::seed()
{
    return r_rng::_seed;
}

bool r_rng::bern(double prob)
{
    std::bernoulli_distribution dist_bern(prob);
    return dist_bern(r_rng::inst);
}

uint32_t r_rng::rng()
{
    return r_rng::uint_dist(r_rng::inst);
}

uint32_t r_rng::rng_range(uint32_t val1, uint32_t val2)
{
    uint32_t min = ( val1 < val2 ) ? val1 : val2;
    uint32_t max = ( val1 < val2 ) ? val2 : val1;
    std::uniform_int_distribution<uint32_t> uint_dist_range( min, max);
    return uint_dist_range(r_rng::inst);
}

int r_rng::binomial(int range, double prob)
{
    std::binomial_distribution<int> dist_binomial(range, prob);
    return dist_binomial(inst);
}

double r_rng::rng_float(double val1, double val2)
{
    double min = ( val1 < val2 ) ? val1 : val2;
    double max = ( val1 < val2 ) ? val2 : val1;
    std::uniform_real_distribution<double> dist_real(min, max);
    return dist_real(inst);
}

double r_rng::normal(double mean, double stddeviation)
{
    std::normal_distribution<double> normal_dist( mean, stddeviation);
    return normal_dist(r_rng::inst);
}

double r_rng::exponential(double lambda)
{
    std::exponential_distribution<double> exp_dist(lambda);
    return exp_dist(r_rng::inst);
}

int r_rng::dice (int number, int sides)
{
    int ret = 0;
    for( int i = 0; i < number; i++)
    {
        ret += r_rng::rng_range( 1, sides);
    }
    return ret;
}