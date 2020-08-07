#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


int main() {
    ifstream input("input.txt");
    double number;
    cout << fixed << setprecision(3);
    if (input.is_open()){
        while (input >> number){
            cout << number << endl;
        }
    }
    return 0;
}