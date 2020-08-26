#include "tests.h"
#include <exception>

void TestRectangle() {
    Rectangle r(2,4);
    AssertEqual(r.GetArea(), 8, "");
    AssertEqual(r.GetPerimeter(), 12, "");
};

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestRectangle, "TestRectangle");
}