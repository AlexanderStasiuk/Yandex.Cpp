#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    Person(string type, string name): type_(type), name_(name) {};
    virtual void Walk(const string& destination) const {
        cout << type_ << ": " << name_ << " walks to: " << destination << endl;
    }
    const string type_;
    const string name_;
};


class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong) : 
        Person("Student", name), FavouriteSong(favouriteSong) {}

    void Learn() {
        cout << "Student: " << name_ << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student" << ": " << name_ << " walks to: " << destination << endl;
        cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
    }

    void SingSong() {
        cout << "Student: " << name_ << " sings a song: " << FavouriteSong << endl;
    }

public:
    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject) :
        Person("Teacher", name), Subject(subject) {}

    void Teach() {
        cout << "Teacher: " << name_ << " teaches: " << Subject << endl;
    }

public:
    const string Subject;
};


class Policeman : public Person {
public:
    Policeman(const string& name) :
        Person("Policeman", name) {}

    void Check(const Person& p) {
        cout << "Policeman: " << name_ << " checks " << p.type_  << ". " << p.type_ << "'s name is: " << p.name_ << endl;
    }
};


void VisitPlaces(const Person& person, vector<string> places) {
    for (auto place : places) {
        person.Walk(place);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
