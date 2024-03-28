#include <cmath>

class Rational {
public:
    Rational()
            : _numerator(0), _denominator(1) {
    }

    Rational(int numerator, int denominator) {
        if (numerator == 0)
        {
            _numerator = 0;
            _denominator = 1;
            return;
        }
        int GCD = getGreatestCommonDivisor(std::abs(numerator), std::abs(denominator));
        _numerator = numerator / GCD;
        _denominator = denominator / GCD;
        if (_denominator < 0)
        {
            _numerator = -_numerator;
            _denominator = -_denominator;
        }
    }

    [[nodiscard]] int Numerator() const {
        return _numerator;
    }

    [[nodiscard]] int Denominator() const {
        return _denominator;
    }

private:
    static int getGreatestCommonDivisor(int first, int second)
    {
        // Euclid's algorithm
        while (first > 0 and second > 0) {
            if (first > second) {
                first %= second;
            } else {
                second %= first;
            }
        }
        return first + second;
    }
    int _numerator;
    int _denominator;
};