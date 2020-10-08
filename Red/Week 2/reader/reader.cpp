#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

// class ReadingManager {
// public:
//   ReadingManager()
//       : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
//         sorted_users_(),
//         user_positions_(MAX_USER_COUNT_ + 1, -1) {}

//   void Read(int user_id, int page_count) {
//     if (user_page_counts_[user_id] == 0) {
//       AddUser(user_id);
//     }
//     user_page_counts_[user_id] = page_count;
//     int& position = user_positions_[user_id];
//     while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
//       SwapUsers(position, position - 1);
//     }
//   }

//   double Cheer(int user_id) const {
//     if (user_page_counts_[user_id] == 0) {
//       return 0;
//     }
//     const int user_count = GetUserCount();
//     if (user_count == 1) {
//       return 1;
//     }
//     const int page_count = user_page_counts_[user_id];
//     int position = user_positions_[user_id];
//     while (position < user_count &&
//       user_page_counts_[sorted_users_[position]] == page_count) {
//       ++position;
//     }
//     if (position == user_count) {
//         return 0;
//     }
//     // По умолчанию деление целочисленное, поэтому
//     // нужно привести числитель к типу double.
//     // Простой способ сделать это — умножить его на 1.0.
//     return (user_count - position) * 1.0 / (user_count - 1);
//   }

// private:
//   // Статическое поле не принадлежит какому-то конкретному
//   // объекту класса. По сути это глобальная переменная,
//   // в данном случае константная.
//   // Будь она публичной, к ней можно было бы обратиться снаружи
//   // следующим образом: ReadingManager::MAX_USER_COUNT.
//   static const int MAX_USER_COUNT_ = 100'000;

//   vector<int> user_page_counts_;
//   vector<int> sorted_users_;   // отсортированы по убыванию количества страниц
//   vector<int> user_positions_; // позиции в векторе sorted_users_

//   int GetUserCount() const {
//     return sorted_users_.size();
//   }
//   void AddUser(int user_id) {
//     sorted_users_.push_back(user_id);
//     user_positions_[user_id] = sorted_users_.size() - 1;
//   }
//   void SwapUsers(int lhs_position, int rhs_position) {
//     const int lhs_id = sorted_users_[lhs_position];
//     const int rhs_id = sorted_users_[rhs_position];
//     swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
//     swap(user_positions_[lhs_id], user_positions_[rhs_id]);
//   }
// };

class ReadingManager {
    public:
        ReadingManager()
            : pages_users_(MAX_PAGE_COUNT_+1)
        {}

        void Read(int user_id, int page_count) {
            if (users_pages_.count(user_id) != 0 ) {
                int prev_page = users_pages_[user_id];
                pages_users_[prev_page].erase(user_id);
            }
            AddStats(user_id, page_count);
        }

        double Cheer(int user_id) {
            if (users_pages_.count(user_id)==0) {
                return 0;
            }
            const int users_count = users_pages_.size();
            if (users_count == 1) {
                return 1;
            }

            int pages_count = users_pages_.at(user_id);
            int count_of_users_with_less=0;

            for(int i=1; i<pages_count; i++) {
                count_of_users_with_less += pages_users_[i].size();
            }
            return (1.0 * count_of_users_with_less)/(users_count - 1);
        }

    private:
        static const int MAX_PAGE_COUNT_ = 1000;
        map<int, int> users_pages_;
        vector<set<int>> pages_users_;
        void AddStats(int user_id, int page_count) {
            users_pages_[user_id] = page_count;
            pages_users_[page_count].insert(user_id);
        }
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}