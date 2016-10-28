#include <random>
#include "r_rng.h"

namespace r_rng {
    typedef std::mt19937 R_RNG;
    uint32_t seed;  
    R_RNG inst;

    std::uniform_int_distribution<uint32_t> uint_dist;
}

void r_rng::init(uint32_t seed)
{
    r_rng::seed = seed;
    srand(seed);
    r_rng::inst.seed(r_rng::seed);
}

uint16_t r_rng::rng_dist()
{
    return r_rng::uint_dist(r_rng::inst);
}

uint16_t r_rng::rng_dist_range(uint32_t val1, uint32_t val2)
{
    uint32_t min = ( val1 < val2 ) ? val1 : val2;
    uint32_t max = ( val1 < val2 ) ? val2 : val1;
    std::uniform_int_distribution<uint32_t> uint_dist_range( min, max);
    
    return uint_dist_range(r_rng::inst);
}

double r_rng::rng_dist_normal(double mean, double stddeviation)
{
    std::normal_distribution<double>normal_dist( mean, stddeviation);
    return normal_dist(r_rng::inst);
}

long r_rng::rng(long val1, long val2) {
  
    long min = ( val1 < val2 ) ? val1 : val2;
    long max = ( val1 < val2 ) ? val2 : val1;
    return min + long( ( max - min + 1 ) * double(rand() / double( RAND_MAX + 1.0 ) ) );
}

double r_rng::rng_float(double val1, double val2)
{
    double min = ( val1 < val2 ) ? val1 : val2;
    double max = ( val1 < val2 ) ? val2 : val1;
    return min + ( max - min ) * double ( rand() ) / double ( RAND_MAX + 1.0);
}

bool r_rng::one_in( int chance )
{
    return ( chance <= 1 || r_rng::rng_float( 0, chance ) < 1);
}

bool r_rng::x_in_y ( double x, double y)
{
    return ( (double)rand() / RAND_MAX ) <= ( (double)x / y);
}

int r_rng::dice (int number, int sides)
{
    int ret = 0;
    for( int i = 0; i < number; i++)
    {
        ret += rng( 1, sides);
    }
    return ret;
}