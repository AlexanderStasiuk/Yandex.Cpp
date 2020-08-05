#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

class Person {
    public:
        void ChangeFirstName(int year, const string& first_name) {
            dictFirstnames[year] = first_name;
            yearsChangeFirstname.push_back(year);
            sort(begin(yearsChangeFirstname), end(yearsChangeFirstname), 
                [](int i, int j){return i>j;});
        }
        void ChangeLastName(int year, const string& last_name) {
            dictLastnames[year] = last_name;
            yearsChangeLastname.push_back(year);
            sort(begin(yearsChangeLastname), end(yearsChangeLastname),
            [](int i, int j){return i>j;});
        }
        string GetFullName(int year, bool history=false) {
            string firstName = getPartName(yearsChangeFirstname, dictFirstnames, year);
            string lastName = getPartName(yearsChangeLastname, dictLastnames, year);

            if (history==true) {
                vector<string> historyFirstName = getHistoryPartName(yearsChangeFirstname, dictFirstnames, year);
                vector<string> historyLastName = getHistoryPartName(yearsChangeLastname, dictLastnames, year);

                firstName = formatString(firstName, historyFirstName);
                lastName = formatString(lastName, historyLastName);
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
        string GetFullNameWithHistory(int year) {
            return GetFullName(year, true);
        }

    private:
        map<int, string> dictFirstnames;
        map<int, string> dictLastnames;
        vector<int> yearsChangeFirstname;
        vector<int> yearsChangeLastname;

        string formatString(string name, vector<string> history) {
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
            const vector<int>& yearsChangePartName, map<int, string>& dictYearPartName,
            int year) {
            
            vector<string> historyItems;
            string __lastRemember = "";
            
            for (const auto& yearChange: yearsChangePartName) {
                if (yearChange <= year) {
                    if (__lastRemember == "") {
                        __lastRemember = dictYearPartName[yearChange];
                    }
                    if (dictYearPartName[yearChange] != __lastRemember) {
                        historyItems.push_back(dictYearPartName[yearChange]);
                    }
                    __lastRemember = dictYearPartName[yearChange];
                }
            }

            return historyItems;
        }
        
        string getPartName (
            const vector<int>& yearsChangePartName, map<int, string>& dictYearPartName,
            int year) {
            
            string nameString = "";

            for (const auto& yearChange: yearsChangePartName) {
                if (yearChange <= year) {
                    if (nameString == "") {
                        nameString = dictYearPartName[yearChange];
                        break;
                    }
                }
                
            }
            return nameString;
        }
};


int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}
