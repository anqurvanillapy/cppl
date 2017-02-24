/**
 *  Parameter Pack
 *  ==============
 *
 *  Unlike C-style variable arguments but like Python's arbitrary argument
 *  lists, the parameter pack has a name which represents the entire
 *  sequence of arguments, but is not exposed as a single object at
 *  runtime.  It should be manipulated through template metaprogramming at
 *  compile time.
 *
 *  Note: Compile with -std=c++14.
 */

#include <iostream>
#include <tuple>

template <typename... T>
auto
Make_tuple(T&&... args)
{
    return std::make_tuple(args...);
}

int
main(int argc, const char* argv[])
{
    // A meaningless wrapper function for std::make_tuple().
    auto triple = Make_tuple(1, 2, 3);

    // It's barely possible to iterate over a tuple.
    std::cout << std::get<0>(triple) << std::endl;
    std::cout << std::get<1>(triple) << std::endl;
    std::cout << std::get<2>(triple) << std::endl;

    return 0;
}
