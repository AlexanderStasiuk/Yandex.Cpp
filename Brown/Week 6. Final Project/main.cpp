// #include "../framework/test_runner.h"
#include "test_runner.h"

#include "request_handler.h"
#include "json.h"

#include <string>
#include <iostream>

using namespace std;

int main() {
    auto doc = Json::Load(std::cin);
    const auto& rootMap = doc.GetRoot().AsMap();
    auto manager = buildDataBase(rootMap.at("base_requests").AsArray());
    processRequests(manager, rootMap.at("stat_requests").AsArray());

    return 0;
}