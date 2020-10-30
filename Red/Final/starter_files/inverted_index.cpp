#include "inverted_index.h"
#include "parse.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>


InvertedIndex::InvertedIndex(istream& stream) {

    for(string current_document; getline(stream, current_document); ){

        docs.push_back(move(current_document));
        size_t docid = docs.size() - 1;
        for (string_view word : SplitIntoWords(docs.back()) ) {
            auto& docids = index[word];

            if (!docids.empty() && docids.back().docid==docid ) {
                docids.back().rating++;
            } else {
                docids.push_back({docid, 1});
            }
        }
    }
}

const deque<string>& InvertedIndex::GetDocuments() const {
    return docs;
}

const vector<InvertedIndex::Item>& InvertedIndex::Lookup(string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}