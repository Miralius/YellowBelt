#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(string name, string profession)
    : _name(std::move(name))
    , _profession(std::move(profession))
    {}

    // Нам нужно максимально избежать дублирования кода, но при этом потребуем абстрактности Person,
    // поэтому сделаем его деструктор чисто виртуальным. Если же в целях проекта необходимо использовать непосредственно
    // Person, а не только наследников, то достаточно использовать virtual ~Person() = default.
    virtual ~Person() = 0;

    virtual void Walk(const string& destination) const {
        cout << _profession << ": " << _name << " walks to: " << destination << '\n';
    }

    virtual void VisitPlaces(const vector<string>& places) const {
        for (const auto& place : places) {
            Walk(place);
        }
    }

    [[nodiscard]] virtual string GetName() const {
        return _name;
    }

    [[nodiscard]] virtual string GetProfession() const {
        return _profession;
    }

private:
    const string _name;
    const string _profession;
};
// Person абстрактный, но необходимо определение деструктора для работы программы
// (деструктор Person обязательно будет вызван после деструкторов наследников, значит и он должен быть определён)
Person::~Person() = default;

class Student : public Person {
public:
    Student(string name, string favouriteSong)
    : Person(std::move(name), "Student")
    , _favouriteSong(std::move(favouriteSong))
    {}

    ~Student() override = default;

    void Walk(const string& destination) const override {
        // Так и задумано, что Студент идёт и поёт? Сочтем за фичу, а не баг, и оставим как есть.
        // В идеале на ревью было бы спросить автора кода, так задумано или это недоработка.
        Person::Walk(destination);
        SingSong();
    }

    void Learn() const {
        cout << GetProfession() << ": " << GetName() << " learns" << '\n';
    }

    void SingSong() const {
        cout << GetProfession() << ": " << GetName() << " sings a song: " << _favouriteSong << '\n';
    }

private:
    const string _favouriteSong;
};


class Teacher : public Person {
public:
    Teacher(string name, string subject)
    : Person(std::move(name), "Teacher")
    , _subject(std::move(subject))
    {}

    ~Teacher() override = default;

    void Teach() const {
        cout << GetProfession() << ": " << GetName() << " teaches: " << _subject << '\n';
    }

private:
    const string _subject;
};


class Policeman : public Person {
public:
    explicit Policeman(string name)
    : Person(std::move(name), "Policeman")
    {}

    ~Policeman() override = default;

    void Check(const Person& person) const {
        cout << GetProfession() << ": " << GetName() << " checks " << person.GetProfession() << ". "
             << person.GetProfession() << "'s name is: " << person.GetName() << '\n';
    }
};


int main() {
    // Person абстрактный и не инстанцируется
    // Person("Anton", "Programmer");

    const vector<string> places = {"Moscow", "London"};

    Teacher teacher("Jim", "Math");
    teacher.Teach();
    teacher.VisitPlaces(places);

    Student student("Ann", "We will rock you");
    student.Learn();
    student.VisitPlaces(places);

    Policeman policeman("Bob");
    policeman.Check(teacher);
    policeman.Check(student);
    policeman.Check(Policeman{"Jack"});
    policeman.VisitPlaces(places);

    return 0;
}