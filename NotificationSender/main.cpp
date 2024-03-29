//
// Created by F-Mir on 3/29/2024.
//
#include <iostream>
#include <string>
#include <utility>

using namespace std;

void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class INotifier
{
public:
    virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier
{
public:
    [[maybe_unused]] explicit SmsNotifier(string phoneNumber) : _phoneNumber(std::move(phoneNumber)) {}
    void Notify(const string& message) const override
    {
        SendSms(_phoneNumber, message);
    }

private:
    const string _phoneNumber;
};

class EmailNotifier : public INotifier
{
public:
    [[maybe_unused]] explicit EmailNotifier(string email) : _email(std::move(email)) {}
    void Notify(const string& message) const override
    {
        SendEmail(_email, message);
    }

private:
    const string _email;
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