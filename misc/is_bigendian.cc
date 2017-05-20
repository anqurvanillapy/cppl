/**
 *  Is big-endian
 *  =============
 *
 *  Cast an int pointer to a char pointer to see whether the CPU register takes
 *  a word in big endian or not (little endian).
 */

#include <iostream>

bool
is_bigendian()
{
    bool ret;
    unsigned i = 1;
    ret = (*(char *)(&i)) ? false : true;
    return ret;
}

int
main(int argc, const char *argv[])
{
    std::cout << "is big-endian? " << is_bigendian() << std::endl;
    return 0;
}
