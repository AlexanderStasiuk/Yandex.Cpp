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

class Person {
    public:
        void ChangeFirstName(int year, const string& first_name) {
            dict_firstnames[year] = first_name;
            years_change_firstname.push_back(year);
            sort(begin(years_change_firstname), end(years_change_firstname), 
                [](int i, int j){return i>j;});
        }
        void ChangeLastName(int year, const string& last_name) {
            dict_lastnames[year] = last_name;
            years_change_lastname.push_back(year);
            sort(begin(years_change_lastname), end(years_change_lastname),
            [](int i, int j){return i>j;});
        }
        string GetFullName(int year) {
            int change_firstname_year = -1;
            int change_lastname_year = -1;
            for (const auto& year_chfirst: years_change_firstname) {
                if (year_chfirst <= year) {
                    change_firstname_year = year_chfirst;
                    break;
                }
            }
            for (const auto& year_chlast: years_change_lastname) {
                if (year_chlast <= year) {
                    change_lastname_year = year_chlast;
                    break;
                }
            }

            if (change_firstname_year > 0 && change_lastname_year > 0) {
                return dict_firstnames[change_firstname_year] + " " + dict_lastnames[change_lastname_year]; 
            } else if (change_firstname_year > 0) {
                return dict_firstnames[change_firstname_year] + " with unknown last name";
            } else if (change_lastname_year > 0) {
                return dict_lastnames[change_lastname_year] + " with unknown first name";
            } else {
                return "Incognito";
            }
            
        }
    private:
        map<int, string> dict_firstnames;
        map<int, string> dict_lastnames;
        vector<int> years_change_firstname;
        vector<int> years_change_lastname;
};


void Empty() {
    Person person;
    Assert(person.GetFullName(1900) == "Incognito", "Empty not return Incognito");
}

void OnlyFirstName() {
    Person person;
    person.ChangeFirstName(1967, "Tanya");
    Assert(person.GetFullName(1968) == "Tanya with unknown last name", "Only firstname not working");
}

void OnlyLastName() {
    Person person;
    person.ChangeLastName(1967, "Sergeeva");
    Assert(person.GetFullName(1968) == "Sergeeva with unknown first name", "Only lastname not working");
}

void ChangeScenario() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    Assert(person.GetFullName(1900) == "Incognito", "");
    Assert(person.GetFullName(1965) == "Polina with unknown last name", "");
    Assert(person.GetFullName(1990) == "Polina Sergeeva", "");

    person.ChangeFirstName(1970, "Appolinaria");
    Assert(person.GetFullName(1969) == "Polina Sergeeva", "");
    Assert(person.GetFullName(1970) == "Appolinaria Sergeeva", "");
    
    person.ChangeLastName(1968, "Volkova");
    Assert(person.GetFullName(1969) == "Polina Volkova", "");
    Assert(person.GetFullName(1970) == "Appolinaria Volkova", "");
}


int main() {
    TestRunner runner;
    runner.RunTest(Empty, "Empty");
    runner.RunTest(OnlyFirstName, "OnlyFirstName");
    runner.RunTest(OnlyLastName, "OnlyLastName");
    runner.RunTest(ChangeScenario, "ChangeScenario");
    return 0;
}