#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <string_view>
#include <numeric>
#include <future>

using namespace std;

void F1 (istream& document_input, Synchronized<InvertedIndex> &index_tmp) { 
        index_tmp.GetAccess().ref_to_value = InvertedIndex{document_input};
}

SearchServer::SearchServer(istream& document_input) {
    F1(ref(document_input), ref(index));
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
   async_tasks.push_back( async(F1, ref(document_input), ref(index)));
}

void F2(
  istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex> &index_tmp
) {
    
    vector<size_t> docid_count;
    vector<uint64_t> docids;

    for (string current_query; getline(query_input, current_query); ) {
        vector<string_view> words = SplitIntoWords(current_query);
        {
            auto ac = index_tmp.GetAccess();

            const size_t doc_count = ac.ref_to_value.GetDocuments().size();
            docid_count.assign(doc_count, 0);
            docids.resize(doc_count);


            auto &idx = ac.ref_to_value;
            for (const auto& word : words) {
                for (const auto& [docid, rating]: idx.Lookup(word)) {
                    docid_count[docid]+= rating;
                }
            }   
        }
        iota(docids.begin(), docids.end(), 0);
        {
            partial_sort(
                begin(docids),
                Head(docids, 5).end(),
                end(docids),
                [&docid_count](int64_t lhs, int64_t rhs) {
                return pair(docid_count[lhs], -1*lhs) > pair(docid_count[rhs], -1*rhs);
                }
            );
        }
        

        search_results_output << current_query << ':';
        for (size_t docid : Head(docids, 5)) {
            const size_t hit_count = docid_count[docid];
            if (hit_count == 0) {
                break;
            }
            search_results_output << " {"
            << "docid: " << docid << ", "
            << "hitcount: " << hit_count << '}';
        }
        search_results_output << '\n';
    }
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
    async_tasks.push_back( async(F2, ref(query_input), ref(search_results_output), ref(index)));
}

