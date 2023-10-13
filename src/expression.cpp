#include "../include/expression.h"

Add operator+(const Expression & first, const Expression & second)
{
    return Add(first, second);
}
Subtract operator-(const Expression & first, const Expression & second)
{
    return Subtract(first, second);
}
Multiply operator*(const Expression & first, const Expression & second)
{
    return Multiply(first, second);
}
Divide operator/(const Expression & first, const Expression & second)
{
    return Divide(first, second);
}
Negate operator-(const Expression & expr)
{
    return Negate(expr);
}
Conjugate operator~(const Expression & expr)
{
    return Conjugate(expr);
}
