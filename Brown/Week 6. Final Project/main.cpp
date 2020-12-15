// #include "../framework/test_runner.h"
#include "test_runner.h"

#include "request_handler.h"

#include <string>
#include <iostream>

using namespace std;

void testComputeDistance() {
  vector<Station> stations = {Station{"Tolstopaltsevo", 55.611087, 37.20829},
                              Station{"Marushkino", 55.595884, 37.209755},
                              Station{"Rasskazovka", 55.632761, 37.333324}};
  double length = 0.0;
  for (size_t i = 0; i < stations.size() - 1; ++i) {
    length += computeDistance(stations[i], stations[i + 1]);
  }

  length *= 2;
  cout << "length " << length << endl;
}

void testProcessRequests() {
  string str =
      "10\n"
      "Stop Tolstopaltsevo: 55.611087, 37.20829\n"
      "Stop Marushkino: 55.595884, 37.209755\n"
      "Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo "
      "Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye\n"
      "Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka\n"
      "Stop Rasskazovka: 55.632761, 37.333324\n"
      "Stop Biryulyovo Zapadnoye: 55.574371, 37.6517\n"
      "Stop Biryusinka: 55.581065, 37.64839\n"
      "Stop Universam: 55.587655, 37.645687\n"
      "Stop Biryulyovo Tovarnaya: 55.592028, 37.653656\n"
      "Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164\n"
      "3\n"
      "Bus 256\n"
      "Bus 750\n"
      "Bus 751\n";
  istringstream in_stream(str);

  auto manager = buildDataBase(in_stream);
  ostringstream out_stream;
  processRequests(manager, in_stream, out_stream);

  string result =
      "Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length\n"
      "Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length\n"
      "Bus 751: not found\n";
  ASSERT_EQUAL(result, out_stream.str());
}

int main() {
    auto manager = buildDataBase();
    processRequests(manager);

     
    // TestRunner tr;
    // RUN_TEST(tr, testProcessRequests);
    // RUN_TEST(tr, testBuildStation);
    //    RUN_TEST(tr, testComputeDistance);

    return 0;
}