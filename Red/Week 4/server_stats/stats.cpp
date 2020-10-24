#include <stats.h>
#include <algorithm>

Stats::Stats() {
    for (size_t i = 0; i < methods_.size(); ++i) {
		methods_stats[methods_[i]] = 0;
		uris_stats[uris_[i]] = 0;
    }
	uris_stats[uris_[uris_.size()-1]] = 0;
}

void Stats::AddMethod(string_view method) {
    const auto find_iter = find(methods_.begin(), methods_.end(), method);
    if (find_iter == methods_.end()) {
		++methods_stats[*prev(methods_.end())];
    } else {
		++methods_stats[methods_.at(find_iter - methods_.begin())];
    }
}

void Stats::AddUri(string_view uri)
{
	const auto find_iter = find(uris_.begin(), uris_.end(), uri);
    if (find_iter == uris_.end()) {
		++uris_stats[*prev(uris_.end())];
    } else {
		++uris_stats[uris_.at(find_iter - uris_.begin())];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methods_stats;
}


const map<string_view, int>& Stats::GetUriStats() const {
	return uris_stats;
}

HttpRequest ParseRequest(string_view line) {
	auto pos = line.find_first_not_of(' ');
	line.remove_prefix(pos);

	pos = line.find(' ');
	string_view method = string_view(line.data(), pos);
	line.remove_prefix(pos + 1);

	pos = line.find(' ');
	string_view uri = string_view(line.data(), pos);
	line.remove_prefix(pos + 1);

	string_view protocol = string_view(line.data());

	return { method, uri, protocol };
}