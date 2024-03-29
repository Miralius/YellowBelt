//
// Created by F-Mir on 3/29/2024.
//
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure
{
public:
    [[nodiscard]] virtual string Name() const = 0;
    [[nodiscard]] virtual double Perimeter() const = 0;
    [[nodiscard]] virtual double Area() const = 0;
protected:
    inline static double _pi = 3.14;
};

class Triangle : public Figure
{
public:
    Triangle(const double a, const double b, const double c)
    : _a(a)
    , _b(b)
    , _c(c)
    {}

    virtual ~Triangle() = default;

    [[nodiscard]] string Name() const override
    {
        return _name;
    }

    [[nodiscard]] double Perimeter() const override
    {
        return _a + _b + _c;
    }

    [[nodiscard]] double Area() const override
    {
        const double halfPerimeter = Perimeter() / 2;
        return sqrt(halfPerimeter * (halfPerimeter - _a) * (halfPerimeter - _b) * (halfPerimeter - _c));
    }

private:
    inline static const string _name = "TRIANGLE";
    const double _a;
    const double _b;
    const double _c;
};

class Rect : public Figure
{
public:
    Rect(const double a, const double b)
        : _a(a)
        , _b(b)
    {}

    virtual ~Rect() = default;

    [[nodiscard]] string Name() const override
    {
        return _name;
    }

    [[nodiscard]] double Perimeter() const override
    {
        return 2 * (_a + _b);
    }

    [[nodiscard]] double Area() const override
    {
        return _a * _b;
    }

private:
    inline static const string _name = "RECT";
    const double _a;
    const double _b;
};

class Circle : public Figure
{
public:
    explicit Circle(const double r)
        : _r(r)
    {}

    virtual ~Circle() = default;

    [[nodiscard]] string Name() const override
    {
        return _name;
    }

    [[nodiscard]] double Perimeter() const override
    {
        return 2 * _pi * _r;
    }

    [[nodiscard]] double Area() const override
    {
        return _pi * _r * _r;
    }

private:
    inline static const string _name = "CIRCLE";
    const double _r;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
    string figure;
    is >> figure;
    if (figure == "TRIANGLE")
    {
        double a;
        double b;
        double c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }
    else if (figure == "RECT")
    {
        double a;
        double b;
        is >> a >> b;
        return make_shared<Rect>(a, b);
    }
    else if (figure == "CIRCLE")
    {
        double r;
        is >> r;
        return make_shared<Circle>(r);
    }
    return {};
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}