#include <string>
#include <vector>
#include <sstream>
using namespace std;

#define CONCAT(l) var##l
#define CONVERT(l) CONCAT(l)

#define UNIQ_ID CONVERT(__LINE__)

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}