#include "test_runner.h"
// #include "../../framework/test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <string_view>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
private:
    unique_ptr<Worker> next_;
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (next_) {
            next_->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next) {
        next_ = move(next);
    }
};


class Reader : public Worker {
private:
    istream& in_stream_;

    istream& ReadField(istream& is, string& field, bool& indicator) {
        indicator = false;
        if (is) {
            getline(is, field);
            indicator = true;
        }
        return is;
    }
public:
    explicit Reader(istream& is) : in_stream_(is) {}

    void Process(unique_ptr<Email>) override {}

    void Run() override {
        while(in_stream_) {
            bool indicator = true;
            auto email = make_unique<Email>();
            ReadField(in_stream_, email->from, indicator);
            ReadField(in_stream_, email->to, indicator);
            ReadField(in_stream_, email->body, indicator);
            if (indicator) { // check of having all fields
                PassOn(move(email));
            }
        }
    }

};


class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
private:
    Function func_;
public:
    explicit Filter(Function func) : func_(move(func)) {} 

    void Process(unique_ptr<Email> email) override {
        if (func_(*email)) {
            PassOn(move(email));
        }
    }
};


class Copier : public Worker {
private:
    string to_;
public:
    explicit Copier(string to) : to_(move(to)) {}

    void Process(unique_ptr<Email> email) override {
        if (email->to != to_) {
            auto copy = make_unique<Email>(*email);
            copy->to = to_;
            PassOn(move(email));
            PassOn(move(copy));
        } else {
            PassOn(move(email));
        }
    }
};


class Sender : public Worker {
private:
    ostream& out_;
public:
    explicit Sender(ostream& out) : out_(out) {}

    void Process(unique_ptr<Email> email) override {
        out_    << email->from << '\n'
                << email->to << '\n'
                << email->body << endl;
        PassOn(move(email));
    }
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) {
        workers_.push_back(make_unique<Reader>(in));
    }

  // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        workers_.push_back(make_unique<Filter>(move(filter)));
        return *this;
    }

  // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        workers_.push_back(make_unique<Copier>(move(recipient)));
        return *this;
    }

  // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        workers_.push_back(make_unique<Sender>(out));
        return *this;
    }

  // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        for (auto i = workers_.rbegin(); i != prev(workers_.rend()); i++) {
            (*next(i))->SetNext(move(*i));
        }
        return move(workers_[0]);
    }
private:
    vector<unique_ptr<Worker>> workers_;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
