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


Rational operator +(const Rational& a, const Rational& b) {
    int new_num = a.Numerator()*b.Denominator() + b.Numerator()*a.Denominator();
    int new_denom = a.Denominator()*b.Denominator();
    return Rational(new_num, new_denom);
}

Rational operator -(const Rational& a, const Rational& b) {
    int new_num = a.Numerator()*b.Denominator() - b.Numerator()*a.Denominator();
    int new_denom = a.Denominator()*b.Denominator();
    return Rational(new_num, new_denom);
}

Rational operator *(const Rational& a, const Rational& b) {
    Rational r1 = Rational(a.Numerator(), b.Denominator());
    Rational r2 = Rational(b.Numerator(), a.Denominator());
    return Rational(r1.Numerator()*r2.Numerator(), r1.Denominator()*r2.Denominator());
}

Rational operator /(const Rational& a, const Rational& b) {
    Rational r1 = Rational(a.Numerator(), b.Numerator());
    Rational r2 = Rational(b.Denominator(), a.Denominator());
    return r1*r2; 
}

bool operator ==(const Rational& a, const Rational& b) {
    return ((a.Numerator() == b.Numerator()) && (a.Denominator() == b.Denominator())); 
}

ostream& operator <<(ostream& _stream, const Rational& a) {
    return _stream << a.Numerator() << '/' << a.Denominator();
}

bool operator <(const Rational& a, const Rational& b) {
    float first = float(a.Numerator())/a.Denominator();
    float second = float(b.Numerator())/b.Denominator();
    return (first < second); 
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
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
