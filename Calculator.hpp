//
//  Calculator.hpp
//  cpp
//
//  Created by Ying on 10/19/25.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <iostream>
#include <map>
#include <string>

class Calculator
{
private:
    std::map<std::string, double> variables;
    bool isOperator(char c) const;
    int getPrecedence(char op) const;
    double applyOperation(double a, double b, char op) const;
    std::string infixToPostfix(const std::string &expression);
    double evaluatePostfix(const std::string &postfix);
    void removeSpaces(std::string &str) const;
    bool isValidExpression(const std::string &expression) const;

public:
    Calculator();
    double Calculate(const std::string &expression);

    void setVariable(const std::string &name, double value);
    double getVariable(const std::string &name) const;
    bool variableExists(const std::string &name) const;

    void clearVariable();
    void displayHelp() const;
};

#endif /* Calculator_hpp */
