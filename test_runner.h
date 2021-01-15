#include <sstream>
#include <exception>
#include <iostream>
#include <string>
#include <map>
#include <set>

template<class T, class U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertNotEqual(const T& t, const U& u, const std::string& hint) {
    if (t == u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " == " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertLess(const T& t, const U& u, const std::string& hint) {
    if (t >= u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " >= " << u
           << " hint: " << hint;
        throw std::runtime_error(os.str());
    }
}

template<class T, class U>
void AssertLessOrEqual(const T& t, const U& u, const std::string& hint) {
    if (t > u) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " > " << u
           << " hint: " << hint;
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
            std::cerr << test_name << " fail: " << e.what() << std::endl;
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
