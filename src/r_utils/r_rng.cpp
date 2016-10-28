#include <random>
#include "r_rng.h"

long rng(int val1, int val2)
{
    long min = ( val1 < val2 ) ? val1 : val2;
    long max = ( val1 < val2 ) ? val2 : val1;
    return min + long( ( max - min + 1 ) * double(rand() / double( RAND_MAX + 1.0 ) ) );
}

double rng_double(double val1, double val2)
{
    double min = ( val1 < val2 ) ? val1 : val2;
    double max = ( val1 < val2 ) ? val2 : val1;
    return min + ( max - min ) * double ( rand() ) / double ( RAND_MAX + 1.0);
}

bool one_in( int chance )
{
    return ( chance <= 1 || rng_double( 0, chance ) < 1);
}

bool x_in_y ( double x, double y)
{
    return ( (double)rand() / RAND_MAX ) <= ( (double)x / y);
}

int dice (int number, int sides)
{
    int ret = 0;
    for( int i = 0; i < number; i++)
    {
        ret += rng( 1, sides);
    }
    return ret;
}