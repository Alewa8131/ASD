// Copyright 2025 Alewa8131

#include <string>

enum class TypeLexem {
    Constant,
    Variable,
    OpenBracket,    // (, [, {
    ClosedBracket,  // ), ], }
    Function,       // sin, cos, tg, ln, exp
    Operator,       // бинарные +, -, *, /, ^ 
    UnOperator,     // унарные -
    OpenedAbs,
    ClosedAbs
};

struct Lexem {
    std::string name;
    TypeLexem type;
    double value;
    int priority;
    double (*function)(double);

    Lexem(std::string _name = "",
        TypeLexem _type = TypeLexem::Constant,
        double _value = DBL_MAX,
        int _priority = -1,
        double (*_function)(double) = nullptr)
        : name(std::move(_name)),
        type(_type),
        value(_value),
        priority(_priority),
        function(_function)
    {}

    bool isConstant() const { return type == TypeLexem::Constant; }
    bool isVariable() const { return type == TypeLexem::Variable; }
    bool isFunction() const { return type == TypeLexem::Function; }
    bool isOperator() const { return type == TypeLexem::Operator; }
    bool isUnOperator() const { return type == TypeLexem::UnOperator; }
    bool isOpenBracket() const { return type == TypeLexem::OpenBracket; }
    bool isClosedBracket() const { return type == TypeLexem::ClosedBracket; }
    bool isOpenedAbs() const { return type == TypeLexem::OpenedAbs; }
    bool isClosedAbs() const { return type == TypeLexem::ClosedAbs; }
};
