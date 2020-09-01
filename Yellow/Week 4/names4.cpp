#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

class Person {
    public:
        void ChangeFirstName(int year, const string& first_name) {
            dict_firstnames[year] = first_name;
        }
        void ChangeLastName(int year, const string& last_name) {
            dict_lastnames[year] = last_name;
        }
        string GetFullName(int year) {
            int firstname_year = -1;
            int lastname_year = -1 ;

            auto iter = dict_firstnames.upper_bound(year);
            if (iter != dict_firstnames.begin()) {
                firstname_year = prev(iter)->first;
            }
            iter = dict_lastnames.upper_bound(year);
            if (iter != dict_lastnames.begin()) {
                lastname_year = prev(iter)->first;
            }

            if (firstname_year > 0 && lastname_year > 0) {
                return dict_firstnames[firstname_year] + " " + dict_lastnames[lastname_year]; 
            } else if (firstname_year > 0) {
                return dict_firstnames[firstname_year] + " with unknown last name";
            } else if (lastname_year > 0) {
                return dict_lastnames[lastname_year] + " with unknown first name";
            } else {
                return "Incognito";
            }
            
        }
    private:
        map<int, string> dict_firstnames;
        map<int, string> dict_lastnames;
};


int main() {
    Person person;
    
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    return 0;
}
