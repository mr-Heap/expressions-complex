#pragma once

#include "complex.h"

#include <functional>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

struct Expression
{
    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const = 0;

    virtual Expression * clone() const = 0;

    friend std::ostream & operator<<(std::ostream & out, const Expression & expression)
    {
        expression.print(out);
        return out;
    }

    virtual ~Expression() = default;

protected:
    virtual void print(std::ostream & out) const = 0;
};

struct Const final : Expression
{
    Const(Complex number)
        : number(std::move(number))
    {
    }

    virtual Complex eval(std::map<std::string, Complex> const & = {}) const override
    {
        return number;
    };

    virtual Expression * clone() const override
    {
        return new Const(number);
    };

protected:
    virtual void print(std::ostream & out) const override
    {
        out << number;
    }

private:
    Complex number;
};

struct Variable final : Expression
{
    Variable(const std::string_view & variable)
        : variable(variable)
    {
    }

    virtual Complex eval(std::map<std::string, Complex> const & values = {}) const override
    {
        return values.at(variable);
    };

    virtual Expression * clone() const override
    {
        return new Variable(variable);
    };

protected:
    virtual void print(std::ostream & out) const override
    {
        out << variable;
    }

private:
    std::string variable;
};

template <char symbol, typename Operation>
struct UnaryOperation final : Expression
{

    UnaryOperation(const Expression & expression)
        : expression(expression.clone())
    {
    }

    Expression * clone() const override
    {
        return new UnaryOperation(*this);
    };

    Complex eval(std::map<std::string, Complex> const & values = {}) const override
    {
        return operation(expression->eval(values));
    };

protected:
    virtual void print(std::ostream & out) const override
    {
        out << "(";
        out << symbol;
        out << *expression;
        out << ")";
    }

private:
    std::shared_ptr<Expression> expression;
    [[no_unique_address]] Operation operation;
};

using Negate = UnaryOperation<'-', std::negate<>>;
using Conjugate = UnaryOperation<'~', std::bit_not<>>;

template <char symbol, typename Operation>
struct BinaryOperation final : Expression
{

    BinaryOperation(const Expression & first, const Expression & second)
        : first(first.clone())
        , second(second.clone())
    {
    }

    Expression * clone() const override
    {
        return new BinaryOperation(*this);
    };

    Complex eval(std::map<std::string, Complex> const & values = {}) const override
    {
        return operation(first->eval(values), second->eval(values));
    };

protected:
    virtual void print(std::ostream & out) const override
    {
        out << "(";
        out << *first;
        out << ' ' << symbol << ' ';
        out << *second;
        out << ")";
    }

private:
    std::shared_ptr<Expression> first;
    std::shared_ptr<Expression> second;
    [[no_unique_address]] Operation operation;
};

using Add = BinaryOperation<'+', std::plus<>>;
using Subtract = BinaryOperation<'-', std::minus<>>;
using Multiply = BinaryOperation<'*', std::multiplies<>>;
using Divide = BinaryOperation<'/', std::divides<>>;

Add operator+(const Expression & first, const Expression & second);

Subtract operator-(const Expression & first, const Expression & second);

Multiply operator*(const Expression & first, const Expression & second);

Divide operator/(const Expression & first, const Expression & second);

Negate operator-(const Expression & expr);

Conjugate operator~(const Expression & expr);
