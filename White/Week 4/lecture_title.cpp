#include<string>
using namespace std;


struct Specialization {
    string value;
    explicit Specialization (string name) {
        value = name;
    }
};

struct Course {
    string value;
    explicit Course (string name) {
        value = name;
    }
};

struct Week {
    string value;
    explicit Week (string name) {
        value = name;
    }
};

struct LectureTitle {
    LectureTitle (Specialization _spec, Course _course, Week _week) {
        specialization = _spec.value;
        course = _course.value;
        week = _week.value;
    }
    string specialization;
    string course;
    string week;
};


int main() {
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
    );
}