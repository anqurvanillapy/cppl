/**
 *  Increment with MP
 *  =================
 *
 *  An example of using OpenMP pragma.  Maybe it is not even faster than the
 *  single core version but using some benchmarking tools like `time' command
 *  can actually indicate that it utilizes multiple hyperthreads now.
 *
 *  Note: Compile with -fopenmp.
 */

#include <iostream>

double n{0.0};

void
inc()
{
    for (unsigned i = 0; i < 42000000; ++i) n += 0.1;
}

void
inc_mp()
{
#pragma omp parallel for schedule(dynamic) reduction(+:n)
    for (unsigned i = 0; i < 42000000; ++i) n += 0.1;
}

int
main(int argc, const char *argv[])
{
    // inc();
    inc_mp();
    std::cout << n << std::endl;
    return 0;
}
