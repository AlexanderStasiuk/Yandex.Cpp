#include "Common.h"

#include <mutex>
#include <list>
#include <unordered_map>

using namespace std;

class LruCache : public ICache {
private:
    shared_ptr<IBooksUnpacker> unpacker_;
    Settings settings_;

    mutex mutex_;

    size_t current_cache_size_;
    list<BookPtr> ranged_books_;
    unordered_map<string, list<BookPtr>::iterator> cache_;
public:
    LruCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const Settings& settings
    ) : unpacker_(books_unpacker),
        settings_(settings),
        current_cache_size_(0) {}

    BookPtr GetBook(const string& book_name) override {
        
        lock_guard guard(mutex_);

        if (cache_.count(book_name)) {
            BookPtr book_ptr = move(*cache_[book_name]);
            ranged_books_.erase(cache_[book_name]);
            ranged_books_.push_back(move(book_ptr));
            cache_[book_name] = prev(ranged_books_.end());
        } else {
            unique_ptr<IBook> book = unpacker_->UnpackBook(book_name);

            while (!cache_.empty() && current_cache_size_ + book->GetContent().size() > settings_.max_memory) {
                BookPtr book_ptr = move(*ranged_books_.begin());
                cache_.erase(book_ptr->GetName());
                current_cache_size_ -= book_ptr->GetContent().size();
                ranged_books_.pop_front();
            }

            if (book->GetContent().size() > settings_.max_memory) {
                return move(book);
            }

            ranged_books_.push_back(move(book));
            cache_[book_name] = prev(ranged_books_.end());
            current_cache_size_ += ranged_books_.back()->GetContent().size();
        }

        return *cache_[book_name];
    }
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
    auto cache = make_unique<LruCache>(move(books_unpacker), settings);
    return cache;
}
