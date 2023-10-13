#pragma once

#include <cmath>
#include <iosfwd>

struct Complex
{

public:
    Complex(double real_part = 0, double image_part = 0)
        : real_part(real_part)
        , image_part(image_part)
    {
    }

    double real() const;

    double imag() const;

    double abs() const;

    std::string str() const;

    friend Complex operator+(const Complex & first, const Complex & second);

    friend Complex operator-(const Complex & first, const Complex & second);

    friend Complex operator*(const Complex & first, const Complex & second);

    friend Complex operator/(const Complex & first, const Complex & second);

    Complex & operator+=(const Complex & second);

    Complex & operator-=(const Complex & second);

    Complex & operator*=(const Complex & second);

    Complex & operator/=(const Complex & second);

    friend Complex operator-(const Complex & second);

    friend Complex operator~(const Complex & second);

    friend bool operator==(const Complex & first, const Complex & second);

    friend bool operator!=(const Complex & first, const Complex & second);

    friend std::ostream & operator<<(std::ostream & out, const Complex & x);

private:
    double real_part;
    double image_part;
};
