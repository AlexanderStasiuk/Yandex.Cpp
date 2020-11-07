#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <optional>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
  {
  }

  Iterator begin() const {
    return first;
  }

  Iterator end() const {
    return last;
  }

private:
  Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
  return IteratorRange{v.begin(), next(v.begin(), min(top, v.size()))};
}

struct Person {
  string name;
  int age, income;
  bool is_male;
};

vector<Person> ReadPeople(istream& input) {
  int count;
  input >> count;

  vector<Person> result(count);
  for (Person& p : result) {
    char gender;
    input >> p.name >> p.age >> p.income >> gender;
    p.is_male = gender == 'M';
  }

  return result;
}

class SocialStats {
private:
    const vector<Person> people;
    std::map<int, int> wealthy_stats; 
    std::optional<std::string> most_popular_M_name;
    std::optional<std::string> most_popular_W_name;
public:
    explicit SocialStats(istream& is) : people( [](){
            vector<Person> temp_people_list = ReadPeople(cin);
            sort(begin(temp_people_list), end(temp_people_list), [](const Person& lhs, const Person& rhs) {
                return lhs.age < rhs.age;
            });
            return temp_people_list;
        }()
    ) {
        map<string, int> M_name_stats;
        map<string, int> W_name_stats;
        int max_number_M = 0;
        int max_number_W = 0;
        for (const Person& person: people) {
            wealthy_stats[person.income]++;

            if (person.is_male) {
                M_name_stats[person.name]++;
                if (M_name_stats[person.name] > max_number_M) {
                    max_number_M = M_name_stats[person.name];
                    most_popular_M_name = person.name;
                }
                if (M_name_stats[person.name] == max_number_M && person.name < most_popular_M_name) {
                    most_popular_M_name = person.name;
                }
            } else {
                W_name_stats[person.name]++;
                if (W_name_stats[person.name] > max_number_W) {
                    max_number_W = W_name_stats[person.name];
                    most_popular_W_name = person.name;
                }
                if (W_name_stats[person.name] == max_number_W && person.name < most_popular_W_name) {
                    most_popular_W_name = person.name;
                }
            }

        }
    }

    int NumberOfAdult(int adult_age) {
        auto adult_begin = lower_bound(
                begin(people), end(people), adult_age, [](const Person& lhs, int age) {
                    return lhs.age < age;
                }
            );
        return people.end() - adult_begin;
    }

    std::optional<string> MostPopularName(char gender) {
        if (gender == 'M') {
            return most_popular_M_name;
        } else {
            return most_popular_W_name;
        }
    }

    int WealthyOfTopPerson(int numberPerson) {
        int currentNumberPerson = 0;
        int wealthy = 0;
        int mult = 0;
        for(auto i = wealthy_stats.rbegin(); currentNumberPerson < numberPerson; i++) {
            mult = i->second;
            if (currentNumberPerson + mult > numberPerson) {
                mult = numberPerson - currentNumberPerson;
            }
            wealthy += mult*i->first;
            currentNumberPerson += mult;
        }
        return wealthy;
    }

};

int main() {
    
    SocialStats social_stat_engine = SocialStats{cin};

    for (string command; cin >> command; ) {
        if (command == "AGE") {
            int adult_age;
            cin >> adult_age;
            cout << "There are " << social_stat_engine.NumberOfAdult(adult_age)
                << " adult people for maturity age " << adult_age << endl;

        } else if (command == "WEALTHY") {
            int count;
            cin >> count;
            int total_income = social_stat_engine.WealthyOfTopPerson(count);
            cout << "Top-" << count << " people have total income " << total_income << '\n';

        } else if (command == "POPULAR_NAME") {
            char gender;
            cin >> gender;
            auto most_popular_name = social_stat_engine.MostPopularName(gender);
            if (most_popular_name) {
                cout << "Most popular name among people of gender " << gender << " is "
                << *most_popular_name << endl;
            } else {
                cout << "No people of gender " << gender << endl;
            }

        }
    }
}
