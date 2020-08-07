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
        if ((numerator<0 && denominator>0) || (numerator>0 && denominator<0)) {
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

Rational operator *(Rational a, Rational b) {
    Rational r1 = Rational(a.Numerator(), b.Denominator());
    Rational r2 = Rational(b.Numerator(), a.Denominator());
    return Rational(r1.Numerator()*r2.Numerator(), r1.Denominator()*r2.Denominator());
}

Rational operator /(Rational a, Rational b) {
    Rational r1 = Rational(a.Numerator(), b.Numerator());
    Rational r2 = Rational(b.Denominator(), a.Denominator());
    return r1*r2; 
}

bool operator ==(Rational a, Rational b) {
    return (a.Numerator() == b.Numerator() && a.Denominator() == b.Denominator()); 
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}