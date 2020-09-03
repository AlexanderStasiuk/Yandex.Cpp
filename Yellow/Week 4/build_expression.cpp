#include <iostream>
#include <sstream>
#include <string>
#include <deque>

using namespace std;

class Expression {
public:
    string GetExpression() {
        stringstream s;
        elements.pop_front();
        elements.pop_back();
        for (auto el: elements) {
            s << el;
        }
        return s.str();
    }
    void AddNumber(int number) {
        elements.push_front("(");
        elements.push_back(to_string(number));
        elements.push_back(")");
    }
    void AddOperation(string operation) {
        elements.push_back(" ");
        elements.push_back(operation);
        elements.push_back(" ");
    }
private:
    deque<string> elements;
};


int main() {
    string operation;
    int number;
    cin >> number;

    int n_operations;
    cin >> n_operations;

    Expression exp;
    exp.AddNumber(number);

    for (int i=0; i<n_operations; i++) {
        cin >> operation;
        cin >> number;
        exp.AddOperation(operation);
        exp.AddNumber(number);
    }

    cout << exp.GetExpression();

	return 0;
}