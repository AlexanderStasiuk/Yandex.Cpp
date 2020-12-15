// #include "../framework/test_runner.h"
#include "test_runner.h"

#include "request_handler.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
    auto manager = buildDataBase();
    processRequests(manager);

    return 0;
}