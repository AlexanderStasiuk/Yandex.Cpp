#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;


class Rational {
public:
    Rational(int numerator = 0, int denominator = 1) {
        if (numerator == 0) {
            num=0;
            denom=1;
        }
        num = abs(numerator);
        denom = abs(denominator);
        if (numerator*denominator<0) {
            negative = true;
        }
        reduceFraction();
        if (negative) {
            num *= -1;
        }
    };

    int Numerator() const {
        return num;
    };
    int Denominator() const {
        return denom;
    };

private:
    int num;
    int denom;
    bool negative=false;
    void reduceFraction() {
        int _gcd = gcd(num, denom);
        num /= _gcd;
        denom /= _gcd;
    }
    int gcd(int a, int b) {
        while ((a != 0) && (b != 0)) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }
        return a+b;
    }

};

int main() {
    Rational r;
    cout << r.Numerator() << '/' << r.Denominator();

    Rational re(-4, -6);
    cout << re.Numerator() << '/' << re.Denominator();

    cout << "OK" << endl;
    return 0;
}