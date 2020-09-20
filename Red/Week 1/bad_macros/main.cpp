#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y) out << (x) << endl << (y) << endl

int main() {
    TestRunner tr;
    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5, "red belt");
        ASSERT_EQUAL(output.str(), "5\nred belt\n");
    }, "PRINT_VALUES usage example");

    tr.RunTest([] {
        ostringstream output;
        PRINT_VALUES(output, 5+1, "red belt");
        ASSERT_EQUAL(output.str(), "6\nred belt\n");
    }, "PRINT_VALUES usage example");

    ostringstream output;
    if (true) PRINT_VALUES(cout, "3", 31);
    else PRINT_VALUES(cout, "3", 31);

    return 0;
}
