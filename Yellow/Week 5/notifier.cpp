#include <iostream>
#include <string>

using namespace std;

class INotifier {
public:
    virtual void Notify(const string& message) const = 0;
};

void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class EmailNotifier : public INotifier {
public:
    EmailNotifier(const string& email_address) : email(email_address) {
    }
    void Notify(const string& message) const override {
        SendEmail(email, message);
    };
private:
    const string email;
};

void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

class SmsNotifier : public INotifier {
public:
    SmsNotifier(const string& phone_number) : number(phone_number) {
    }
    void Notify(const string& message) const override {
        SendSms(number, message);
    };
private:
    const string number;
};

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}