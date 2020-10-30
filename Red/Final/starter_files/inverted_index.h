#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
using namespace std;

class InvertedIndex {
public:
    InvertedIndex() = default ;
    explicit InvertedIndex(istream& is);

    struct Item {
        size_t docid;
        size_t rating;
    };

    // void Add(string&& document);
    const vector<Item>& Lookup(string_view word) const ;

    const deque<string>& GetDocuments() const;
private:
    map <string_view, vector<Item> > index;
    deque<string> docs;
};
