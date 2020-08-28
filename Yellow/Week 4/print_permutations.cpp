#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> GetPermutations(int n) {
    bool flag = true;
    vector<vector<int>> res;
    vector<int> permutation;
    for (int i=n; i>0; i--) {
        permutation.push_back(i);
    }
    

    while(flag == true) {
        res.push_back(permutation);
        flag = next_permutation(
            begin(permutation), end(permutation),
            [](int lhs, int rhs){
                return lhs > rhs;
            }
        );
    }
    return res;
}

void PrintPermutations(const vector<vector<int>>& permutations) {
    for (vector<int> permutation: permutations) {
        for (int element: permutation) {
            cout << element << ' ';
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> permutations = GetPermutations(n);
    PrintPermutations(permutations);
    return 0;
}