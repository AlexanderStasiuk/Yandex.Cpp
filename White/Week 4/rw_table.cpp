#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;


int main() {
    ifstream input("input.txt");
    int n, m;
    int element;

    if (input.is_open()){
        input >> n >> m;
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++){
                input >> element;
                input.ignore(1);
                if (j != 0) {
                    cout << ' ';
                }
                cout << setw(10) << element;
            }
            if (i<n-1) {
                cout << endl;
            }
        }
    }
    return 0;
}