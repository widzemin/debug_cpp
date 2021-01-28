#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <ostream>
#include "collection_out.cpp"

using namespace Debug;

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed:\n" << t << " != " << u << "\n"
           << "Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertNotEqual(const T& t, const U& u, const std::string& hint) {
    if (t == u) {
        std::ostringstream os;
        os << "Assertion failed:\n" << t << " == " << u << "\n"
           << "Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertLess(const T& t, const U& u, const std::string& hint) {
    if (t >= u) {
        std::ostringstream os;
        os << "Assertion failed:\n" << t << " >= " << u << "\n"
           << "Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertLessOrEqual(const T& t, const U& u, const std::string& hint) {
    if (t > u) {
        std::ostringstream os;
        os << "Assertion failed:\n" << t << " > " << u << "\n"
           << "Hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string& test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::runtime_error& e) {
            ++fail_count;
            std::cerr << test_name << " " << "fail:" << std::endl;
            std::cerr << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception" << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    size_t fail_count = 0;
};

#define RUN_TEST(tr, func)                                              \
  tr.RunTest(func, #func)

#define ASSERT_EQUAL(x, y) {                                            \
  ostringstream __assert_equal_private_os;                              \
  __assert_equal_private_os <<                                          \
    #x << " != " << #y << "\n"                                          \
    << "In file : " << __FILE__ << "\n"                                 \
    << "In line : " << __LINE__ << "\n";                                \
  AssertEqual(x, y, __assert_equal_private_os.str());                   \
}

#define ASSERT(x) {                                                     \
  ostringstream __assert_private_os;                                    \
  __assert_private_os                                                   \
    << #x << " is false" << "\n"                                        \
    << "In file : " << __FILE__ << "\n"                                 \
    << "In line : " << __LINE__;                                        \
  Assert(x, __assert_private_os.str());                                 \
}

#define ASSERT_NOT_EQUAL(x, y) {                                        \
    ostringstream __assert_not_equal_private_os;                        \
    __assert_equal_private_os                                           \
      << #x << " == " << #y << "\n"                                     \
      << "In file : " << __FILE__ << "\n"                               \
      << "In line : " << __LINE__;                                      \
    AssertNotEqual(x, y, __assert_equal_private_os.str());              \
}


#define ASSERT_LESS(x, y) {                                             \
    ostringstream __assert_less_private_os;                             \
    __assert_less_private_os                                            \
      << #x << " >= " << #y << "\n"                                     \
      << "In file : " << __FILE__ << "\n"                               \
      << "In line : " << __LINE__;                                      \
    AssertLess(x, y, __assert_less_private_os.str());                   \
}

#define ASSERT_LESS_OR_EQUAL(x, y) {                                    \
    ostringstream __assert_less_or_equal_private_os;                    \
    __assert_less_or_equal_private_os                                   \
      << #x << " > " << #y << "\n"                                      \
      << "In file : " << __FILE__ << "\n"                               \
      << "In line : " << __LINE__;                                      \
    AssertLessOrEqual(x, y, __assert_less_or_equal_private_os.str());   \
}

