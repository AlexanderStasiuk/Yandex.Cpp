#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <math.h>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Rect : public Figure {
public:
    Rect(const int& width, const int& height) : width_(width), height_(height) {
    }
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return (2*width_ + 2*height_);
    }
    double Area() const override {
        return (width_*height_);
    }
private: 
    const string name_ = "RECT";
    const int width_;
    const int height_;
};

class Triangle : public Figure {
public:
    Triangle(const int& a, const int& b, const int& c) : a_(a), b_(b), c_(c) {
    }
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return (a_ + b_ + c_);
    }
    double Area() const override {
        double p = Perimeter()/2;
        return sqrt(p*(p-a_)*(p-b_)*(p-c_));
    }
private: 
    const string name_ = "TRIANGLE";
    const double a_, b_, c_;
};

class Circle : public Figure {
public:
    Circle(const int& r) : r_(r) {
    }
    string Name() const override {
        return name_;
    }
    double Perimeter() const override {
        return (2*pi_*r_);
    }
    double Area() const override {
        return pi_*r_*r_;
    }
private: 
    const string name_ = "CIRCLE";
    const double r_;
    const double pi_ = 3.14;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string type;
    is >> type;

    if (type == "RECT") {
        int width, height;
        is >> width >> height; 
        return make_shared<Rect>(width, height);
    } else if (type == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    } 
}


int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}