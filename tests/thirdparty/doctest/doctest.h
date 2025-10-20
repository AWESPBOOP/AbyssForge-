#pragma once
#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace doctest {

struct TestFailure : std::runtime_error {
    using std::runtime_error::runtime_error;
};

inline void check(bool condition, const char *expr, const char *file, int line)
{
    if (!condition) {
        std::ostringstream oss;
        oss << file << ":" << line << " CHECK(" << expr << ") failed";
        throw TestFailure(oss.str());
    }
}

#define DOCTEST_CHECK(expr) ::doctest::check((expr), #expr, __FILE__, __LINE__)

class TestSuite {
public:
    using TestFunc = void (*)();

    static TestSuite &instance()
    {
        static TestSuite suite;
        return suite;
    }

    void add(TestFunc func) { m_funcs.push_back(func); }

    int run()
    {
        try {
            for (auto func : m_funcs) {
                func();
            }
        } catch (const TestFailure &failure) {
            std::cerr << failure.what() << "\n";
            return 1;
        }
        std::cout << "All doctest-style tests passed\n";
        return 0;
    }

private:
    std::vector<TestFunc> m_funcs;
};

class TestRegistrar {
public:
    explicit TestRegistrar(TestSuite::TestFunc func) { TestSuite::instance().add(func); }
};

} // namespace doctest

#define DOCTEST_TEST_CASE(name)                                                                                              \
    static void name();                                                                                                      \
    static ::doctest::TestRegistrar name##_registrar{name};                                                                  \
    static void name()

int main()
{
    return ::doctest::TestSuite::instance().run();
}

#endif // DOCTEST_LIBRARY_INCLUDED
