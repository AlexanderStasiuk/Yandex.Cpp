#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational {
public:
    Rational(int numerator = 0, int denominator = 1) {
        if (denominator == 0) {
            throw invalid_argument("Denominator can't be equal 0");
        }
        if (numerator == 0) {
            num=0;
            denom=1;
        }
        num = abs(numerator);
        denom = abs(denominator);
        if ((numerator<0 && denominator>0) || (numerator>0 && denominator<0)) {
            negative = true;
        }
        reduceFraction();
        if (negative) {
            num *= -1;
        }
    };
    int Numerator() const {
        return num;
    };
    int Denominator() const {
        return denom;
    };

private:
    int num;
    int denom;
    bool negative=false;
    void reduceFraction() {
        int _gcd = gcd(num, denom);
        num /= _gcd;
        denom /= _gcd;
    }
    int gcd(int a, int b) {
        while ((a != 0) && (b != 0)) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }
        return a+b;
    }
};

void Empty() {
    Rational r;
    Assert(r.Numerator() == 0, "Numerator incorrect");
    Assert(r.Denominator() == 1, "Denominator incorrect");
}

void Simple() {
    Rational r = {2, 3};
    Assert(r.Numerator() == 2, "Numerator incorrect");
    Assert(r.Denominator() == 3, "Denominator incorrect");
}

void NumeratorIsZero() {
    Rational r = {0, 3};
    Assert(r.Numerator() == 0, "Numerator incorrect");
    Assert(r.Denominator() == 1, "Denominator incorrect");
}

void NegativeDenominator() {
    Rational r = {2, -3};
    Assert(r.Numerator() == -2, "Numerator incorrect");
    Assert(r.Denominator() == 3, "Denominator incorrect");
}

void NegativeBoth() {
    Rational r = {-2, -3};
    Assert(r.Numerator() == 2, "Numerator incorrect");
    Assert(r.Denominator() == 3, "Denominator incorrect");
}

void ReduceFraction() {
    Rational r = {24, 16};
    Assert(r.Numerator() == 3, "Numerator incorrect");
    Assert(r.Denominator() == 2, "Denominator incorrect");

    Rational r2 = {24, -16};
    Assert(r2.Numerator() == -3, "Numerator incorrect");
    Assert(r2.Denominator() == 2, "Denominator incorrect");
}

int main() {
    TestRunner runner;
    runner.RunTest(Empty, "Empty");
    runner.RunTest(Simple, "Simple");
    runner.RunTest(NumeratorIsZero, "NumeratorIsZero");
    runner.RunTest(NegativeDenominator, "NegativeDenominator");
    runner.RunTest(NegativeBoth, "NegativeBoth");
    runner.RunTest(ReduceFraction, "ReduceFraction");
    return 0;
}