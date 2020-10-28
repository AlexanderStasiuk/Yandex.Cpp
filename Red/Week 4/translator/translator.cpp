#include "test_runner.h"
#include <string>
#include <vector>
#include <string_view>
#include <deque>
#include <map>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        const auto source_pos = source_to_target_.find(source);
        const auto target_pos = target_to_source_.find(target);

        if (source_pos == source_to_target_.end() && target_pos == target_to_source_.end()) {
            storage_.push_front(std::string(source));
            storage_.push_front(std::string(target));

            source_to_target_[*std::next(storage_.begin())] = *storage_.begin();
            target_to_source_[*storage_.begin()] = *std::next(storage_.begin());
        }
        else if (target_pos == target_to_source_.end()) {
            storage_.push_front(std::string(target));
            source_to_target_[source] = *storage_.begin();
            target_to_source_[*storage_.begin()] = source_pos->first;
        }
        else if (source_pos == source_to_target_.end()) {
            storage_.push_front(std::string(source));
            target_to_source_[target] = *storage_.begin();
            source_to_target_[*storage_.begin()] = target_pos->first;
        }
    }
    string_view TranslateForward(string_view source) const {
        try {
		    return source_to_target_.at(source);
        } catch (std::out_of_range&) {
		    return "";
        }
    }
    string_view TranslateBackward(string_view target) const {
        try {
		    return target_to_source_.at(target);
        } catch (std::out_of_range&) {
		    return "";
        }
    }

private:
    map<std::string_view, std::string_view> source_to_target_;
	map<std::string_view, std::string_view> target_to_source_;
	deque<std::string> storage_;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
