#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

// Solution O(n*m)


bool IsSubdomain(const string& subdomain, const string& domain) {
    size_t subd_size = subdomain.size();
    if (subd_size < domain.size()) {
        return false;
    }
    for (int i=domain.size()-1; i > -1; i--) {
        if (domain.at(i) != subdomain.at(subd_size-domain.size()+i)) {
            return false;
        }
    }

    if (subd_size != domain.size() && subdomain.at(subd_size-domain.size()-1) != '.') {
        return false;
    }

    return true;
}


// int main() {
//     vector<string> banned_domains;
//     vector<string> domains_to_check;
//     string domain;
//     size_t domains_count;
//     cin >> domains_count;

//     for (size_t i = 0; i < domains_count; i++) {
//         cin >> domain;
//         banned_domains.push_back(domain);
//     }

//     cin >> domains_count;

//     for (size_t i = 0; i < domains_count; i++) {
//         cin >> domain;
//         domains_to_check.push_back(domain);
//     }

//     for (const string& subdomain : domains_to_check) {
//         bool flag = true;
//         for (const string& domain : banned_domains) {
//             if (IsSubdomain(subdomain, domain)) {
//                 cout << "Bad" << endl;
//                 flag = false;
//                 break;
//             }
//         } 
//         if (flag) cout << "Good" << endl;
//     }
//     return 0;
// }
