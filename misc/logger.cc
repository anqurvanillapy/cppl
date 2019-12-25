/**
 * Logger
 * ======
 *
 * A simple log recorder/dumper.
 *
 * Note: Compile with -std=c++17.
 */

#include <vector>
#include <sstream>
#include <iostream>

class Log final {
public:
    template <typename... Args>
    static int Record(int err, Args&&... args)
    {
        std::ostringstream stream{};
        ((stream << "(err: " << err << ") ") << ... << args);
        trace_.emplace_back(stream.str());
        return err;
    }

    static std::string Dump()
    {
        std::ostringstream stream{};
        for (const auto &s : trace_) {
            stream << s << '\n';
        }
        return stream.str();
    }
private:
    Log() {}

    static thread_local std::vector<std::string> trace_;
};

thread_local std::vector<std::string> Log::trace_{};

constexpr auto OK = 0;
constexpr auto ERR = 1;

int C(int data)
{
    int val = data + 100;

    return Log::Record(ERR, "C=", val);
}

int B(int data)
{
    int val = data * 2;

    if (auto rc = C(val); rc != OK) {
        return Log::Record(rc, "B=", val);
    }

    return OK;
}

int A(int data)
{
    int val = data;

    if (auto rc = B(val); rc != OK) {
        return Log::Record(rc, "A=", val);
    }

    return OK;
}

int main()
{
    A(42);
    std::cerr << Log::Dump();
    return 0;
}
