#include "../include/complex.h"

#include <iomanip>

double Complex::imag() const
{
    return image_part;
}

double Complex::real() const
{
    return real_part;
}

double Complex::abs() const
{
    return std::hypot(real_part, image_part);
}

std::string Complex::str() const
{
    std::ostringstream out;
    out << *this;
    return out.str();
}

Complex operator+(const Complex & first, const Complex & second)
{
    return Complex(first.real_part + second.real_part, first.image_part + second.image_part);
}

Complex operator-(const Complex & first, const Complex & second)
{
    return Complex(first.real_part - second.real_part, first.image_part - second.image_part);
}

Complex operator*(const Complex & first, const Complex & second)
{
    return Complex(first.real_part * second.real_part - first.image_part * second.image_part,
                   first.image_part * second.real_part + first.real_part * second.image_part);
}

Complex operator/(const Complex & first, const Complex & second)
{
    if (second.real_part == 0 && second.image_part == 0) {
        return Complex(first.real_part / second.real_part, first.image_part / second.image_part);
    }
    double r = second.real_part * second.real_part + second.image_part * second.image_part;
    return first * Complex(second.real_part / r, -second.image_part / r);
}

Complex & Complex::operator+=(const Complex & second)
{
    return *this = *this + second;
}

Complex & Complex::operator-=(const Complex & second)
{
    return *this = *this - second;
}

Complex & Complex::operator*=(const Complex & second)
{
    return *this = *this * second;
}

Complex & Complex::operator/=(const Complex & second)
{
    return *this = *this / second;
}

Complex operator-(const Complex & first)
{
    return Complex(-first.real_part, -first.image_part);
}

Complex operator~(const Complex & first)
{
    return Complex(first.real_part, -first.image_part);
}

bool operator==(const Complex & first, const Complex & second)
{
    return first.real_part == second.real_part && first.image_part == second.image_part;
}

bool operator!=(const Complex & first, const Complex & second)
{
    return !(first == second);
}

std::ostream & operator<<(std::ostream & out, const Complex & x)
{
    return out << "(" << x.real_part << "," << x.image_part << ")";
}
