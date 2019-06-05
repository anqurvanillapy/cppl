/**
 *  Lifted boolean
 *  ==============
 */

#include <iostream>

enum lbool {
    l_false = -1,
    l_undef, // undefined
    l_true,
};

constexpr lbool operator~(lbool lb)
{
    return static_cast<lbool>(-static_cast<int>(lb));
}

constexpr lbool to_lbool(bool b)
{
    return static_cast<lbool>(static_cast<int>(b) * 2 - 1);
}

std::ostream& operator<<(std::ostream& out, lbool b)
{
    switch (b) {
        case l_false:
            return out << "l_false";
        case l_true:
            return out << "l_true";
        default:
            return out << "l_undef";
    }
}

int main()
{
    auto lb = l_undef;
    std::cout << lb << std::endl;
    lb = to_lbool(true);
    std::cout << lb << std::endl;
    std::cout << ~lb << std::endl;
    return 0;
}
