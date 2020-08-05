#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

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
