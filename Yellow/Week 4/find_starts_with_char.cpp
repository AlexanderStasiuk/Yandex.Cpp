#include <iostream>
#include <vector>

using namespace std;

// template <typename RandomIt>
// pair<RandomIt, RandomIt> FindStartsWith(
//     RandomIt range_begin, RandomIt range_end,
//     char prefix) {

//     auto left_it = find_if(
//         range_begin, range_end,
//         [prefix](const string& str) {
//             return str[0] == prefix;
//         }
//     );
//     auto right_it = find_if(
//         range_begin, range_end,
//         [prefix](const string& str) {
//             return str[0] > prefix;
//         }
//     );
//     if (left_it == range_end) {
//         left_it = right_it;
//     }
//     return make_pair(left_it, right_it);
// }

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    char prefix) {

    char left_prefix = prefix-1;

    auto left_it = lower_bound(
        range_begin, range_end, left_prefix,
        [](const string& str, const char& c) {
            return str[0] <= c;
        }
    );
    auto right_it = upper_bound(
        range_begin, range_end, prefix,
        [](const char& c, const string& str) {
            return str[0] > c;
        }
    );
    return make_pair(left_it, right_it);
}



int main() {
    const vector<string> sorted_strings = {"dad","moscow", "murmansk", "ndfd", "vologda"};

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}
