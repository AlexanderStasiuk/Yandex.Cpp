#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

bool IsPalindrom(const string& s) {
	int numberOfSymbols = s.size() - 1;
	for (int i=0; i<=numberOfSymbols/2; i++) {
		if (s[i] != s[numberOfSymbols-i]) {
			return false;
		}
	}
	return true;
}

void Success() {
    Assert(IsPalindrom("") == true, "Empty string is a palindrom");
    Assert(IsPalindrom("a") == true, "One_character-string is a palindrom");
    Assert(IsPalindrom("apapa") == true, "Usual case");
    Assert(IsPalindrom("   ") == true, "Only whitespaces is a palindrom");
    Assert(IsPalindrom("!&!") == true, "Non-alphabet characters is a palindrom");
    Assert(IsPalindrom("__  ff  ff  __") == true, "Is palindrom");
}

void Fail() {
    Assert(IsPalindrom(" apap") == false, "First symbol is whitespace");
    Assert(IsPalindrom("apap") == false, "");
    Assert(IsPalindrom("rpapa") == false, "Check first symbol ignoring");
    Assert(IsPalindrom("apapr") == false, "Check last symbol ignoring");
    Assert(IsPalindrom("ap ap a") == false, "Check whitespaces ignoring");
    Assert(IsPalindrom("alsprsla") == false, "Check middle of string");
    Assert(IsPalindrom("баобаб") == false, "Russian characters");
}



int main() {
    TestRunner runner;
    runner.RunTest(Success, "Success");
    runner.RunTest(Fail, "Fail");
    return 0;
}