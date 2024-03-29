#include <iostream>
#include <utility>

using namespace std;

class Animal {
public:
    explicit Animal(string name)
            : Name(std::move(name)) {}

    const string Name;
};


class Dog : public Animal {
public:
    explicit Dog(const string &name)
            : Animal(name) {}

    void Bark() const {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
    const auto dog = Dog("Bax");
    dog.Bark();
    return 0;
}