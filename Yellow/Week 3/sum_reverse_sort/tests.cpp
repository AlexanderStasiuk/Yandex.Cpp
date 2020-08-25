#include "tests.h"
#include <vector>

void TestSum() {
    AssertEqual(Sum(2, 3), 5, "");
    AssertEqual(Sum(-2, 3), 1, "");
    AssertEqual(Sum(-20, 333), 313, "");
    AssertEqual(Sum(-33, 11), -22, "");
    AssertEqual(Sum(-3, 3), 0, "");
    AssertEqual(Sum(-3, 0), -3, "");
};

void TestReverse() {
    AssertEqual(Reverse("1234"), "4321", "");
    AssertEqual(Reverse("asd"), "dsa", "");
    AssertEqual(Reverse("пар"), "рап", "");
    AssertEqual(Reverse(""), "", "");
    AssertEqual(Reverse("    "), "    ", "");
};

void TestSort() {
    vector<int> source;
    vector<int> expect;
    source = {1,3,5,2,4};
    expect = {1,2,3,4,5};
    Sort(source);
    Assert(source == expect, "");
    source = {-1,3,-5,2,4};
    expect = {-5,-1,2,3,4};
    Sort(source);
    Assert(source == expect, "");
};

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestSum, "TestSum");
    tr.RunTest(TestReverse, "TestReverse");
    tr.RunTest(TestSort, "TestSort");
}