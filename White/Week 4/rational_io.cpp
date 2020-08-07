#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
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

ostream& operator <<(ostream& _stream, const Rational& a) {
    return _stream << a.Numerator() << '/' << a.Denominator();
}

istream& operator >>(istream& _stream, Rational& a) {
    if (_stream) {
        int new_num;
        int new_denom;
        char s;
        _stream >> new_num;
        _stream >> s;
        if (s == '/') {
            if (bool(_stream >> new_denom)) {
               a = Rational(new_num, new_denom); 
            }
        }
    }
    return _stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/");
        Rational r1, r2;
        input >> r1 >> r2;
        cout << r1;
        cout << r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}