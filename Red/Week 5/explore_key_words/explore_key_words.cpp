#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <iostream>
#include <string_view>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (const auto& [k,v] : other.word_frequences) {
		    word_frequences[k] += v;
	    }
    }
};

// Stats ExploreLine(const set<string>& key_words, const string& line) {
//     Stats stats;
//     for (const string& word: key_words) {
//         string find_word = word;
//         find_word.insert(0, " ");
//         find_word.insert(find_word.size(), " ");
//         string::size_type pos = 0;
//         while ((pos = line.find(find_word, pos )) != string::npos) {
//             stats.word_frequences[word]++;
//             pos += word.length();
//         }
//     }
//     return stats;
// }

Stats ExploreLine(const std::set<std::string>& key_words, const std::string& line) 
{
    string_view line_view = line;
	Stats result;
	size_t pos = line_view.find_first_not_of(' ');
	line_view.remove_prefix(pos);

    while (pos != line_view.npos) {
		pos = line_view.find_first_of(' ');
		auto key = string(line_view.substr(0, pos));
        if (key_words.count(key) > 0) {
			++result.word_frequences[move(key)];
        }
        if (pos == line_view.npos) {
            break;
        }
		line_view.remove_prefix(pos);
		pos = line_view.find_first_not_of(' ');
		line_view.remove_prefix(pos);
    }

	return result;
}


Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats stats;
    vector<future<Stats>> futures;
    const int num_threads = thread::hardware_concurrency();
    vector<stringstream> streams(num_threads);

    size_t lines_number = 0;
    string line;

    while (getline(input, line)) {
		streams[lines_number % num_threads] << ' ' << line << ' ';
		++lines_number;
    }

    for (auto& s : streams) {
		futures.push_back(async([&] {
			return ExploreKeyWordsSingleThread(ref(key_words), ref(s));
		}));
    }

    for (auto& future : futures) {
		stats += future.get();
    }
	return stats;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
