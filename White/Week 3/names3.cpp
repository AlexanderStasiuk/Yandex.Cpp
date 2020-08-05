#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Person {
    public:
        Person(string firstName, string lastName, int year) {
            dictFirstnames[year] = firstName;
            yearsChangeFirstname.push_back(year);
            dictLastnames[year] = lastName;
            yearsChangeLastname.push_back(year);
            birthYear = year;
        }
        void ChangeFirstName(int year, const string& first_name) {
            if (year>birthYear) {
                dictFirstnames[year] = first_name;
                yearsChangeFirstname.push_back(year);
                sort(begin(yearsChangeFirstname), end(yearsChangeFirstname), 
                    [](int i, int j){return i>j;});
            }
        }
        void ChangeLastName(int year, const string& last_name) {
            if (year>birthYear) {
                dictLastnames[year] = last_name;
                yearsChangeLastname.push_back(year);
                sort(begin(yearsChangeLastname), end(yearsChangeLastname),
                [](int i, int j){return i>j;});
            }
        }
        string GetFullName(int year, bool history=false) const {
            string firstName = getPartName(yearsChangeFirstname, dictFirstnames, year);
            string lastName = getPartName(yearsChangeLastname, dictLastnames, year);

            if (history==true) {
                vector<string> historyFirstName = getHistoryPartName(yearsChangeFirstname, dictFirstnames, year);
                vector<string> historyLastName = getHistoryPartName(yearsChangeLastname, dictLastnames, year);

                firstName = formatString(firstName, historyFirstName);
                lastName = formatString(lastName, historyLastName);
            }

            if (year<birthYear) {
                return "No person";
            }
            

            if (firstName != "" && lastName != "") {
                return firstName + " " + lastName; 
            } else if (firstName != "") {
                return firstName + " with unknown last name";
            } else if (lastName != "") {
                return lastName + " with unknown first name";
            } else {
                return "Incognito";
            }
            
        }
        string GetFullNameWithHistory(int year) const {
            return GetFullName(year, true);
        }

    private:
        int birthYear;
        map<int, string> dictFirstnames;
        map<int, string> dictLastnames;
        vector<int> yearsChangeFirstname;
        vector<int> yearsChangeLastname;

        string formatString(string name, const vector<string>& history) const {
            if (name == "") {
                return "";
            }
            if (history.size() > 0) {
                name += " (";
            }
            
            for (int i=0; i<history.size(); i++) {
                name += history[i];
                if (i < history.size()-1) {
                    name += ", ";
                } else {
                    name += ")";
                }
            }
            return name;
        }

        vector<string> getHistoryPartName(
            const vector<int>& yearsChangePartName, const map<int, string>& dictYearPartName,
            int year) const {
            
            vector<string> historyItems;
            string __lastRemember = "";
            
            for (const auto& yearChange: yearsChangePartName) {
                if (yearChange <= year) {
                    if (__lastRemember == "") {
                        __lastRemember = dictYearPartName.at(yearChange);
                    }
                    if (dictYearPartName.at(yearChange) != __lastRemember) {
                        historyItems.push_back(dictYearPartName.at(yearChange));
                    }
                    __lastRemember = dictYearPartName.at(yearChange);
                }
            }

            return historyItems;
        }
        
        string getPartName (
            const vector<int>& yearsChangePartName, const map<int, string>& dictYearPartName,
            int year) const {
            
            string nameString = "";

            for (const auto& yearChange: yearsChangePartName) {
                if (yearChange <= year) {
                    if (nameString == "") {
                        nameString = dictYearPartName.at(yearChange);
                        break;
                    }
                }
                
            }
            return nameString;
        }
};


int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}