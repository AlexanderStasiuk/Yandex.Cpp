#include <iostream>
#include <vector>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const string& prefix) {

    auto left_it = lower_bound(
        range_begin, range_end, prefix,
        [](const string& str, const string& prefix) {
            return str.substr(0, prefix.size()) < prefix;
        }
    );
    auto right_it = upper_bound(
        range_begin, range_end, prefix,
        [](const string& prefix, const string& str) {
            return str.substr(0, prefix.size()) > prefix;
        }
    );
    return make_pair(left_it, right_it);
}



int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};

    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;

    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;

    return 0;
}

