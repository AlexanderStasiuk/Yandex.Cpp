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


Rational operator +(Rational a, Rational b) {
    int new_num = a.Numerator()*b.Denominator() + b.Numerator()*a.Denominator();
    int new_denom = a.Denominator()*b.Denominator();
    return Rational(new_num, new_denom);
}

Rational operator -(Rational a, Rational b) {
    int new_num = a.Numerator()*b.Denominator() - b.Numerator()*a.Denominator();
    int new_denom = a.Denominator()*b.Denominator();
    return Rational(new_num, new_denom);
}

bool operator ==(Rational a, Rational b) {
    return (a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator()); 
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}