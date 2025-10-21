#include "Calculator.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <cctype>

Calculator::Calculator() {
    variables["PI"] = 3.141592653;
    variables["E"] = 2.71828182845;
}

double Calculator::Calculate(const std::string& expression) {
    if (expression.empty()){
        throw std::invalid_argument("Empty Expression");
    }
    std::string processedExpr = expression;
    removeSpaces(processedExpr);
    
    if (!isValidExpression(processedExpr)) {
        throw std::invalid_argument("Invalid expression: mismatched parentheses");
    }
    
    std::string postfix = infixToPostfix(processedExpr);
    return evaluatePostfix(postfix);
}

bool Calculator::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int Calculator::getPrecedence(char op) const {
    switch (op) {
        case '+': case '-':
            return 1;
        case '*' : case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

double Calculator::applyOperation(double a, double b, char op) const {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        case '^':
            return std::pow(a, b);
        default:
            throw std::invalid_argument("Invalid operator");
    }
}

std::string Calculator::infixToPostfix(const std::string& expression) {
    std::stack<char> operators;
    std::stringstream postfix;
    
    for (size_t i = 0; i < expression.length(); i++) {
        char c = expression[i];
        
        if (isdigit(c) || c == '.') {
            // Handle numbers
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                postfix << expression[i];
                i++;
            }
            i--;
            postfix << ' ';
        }
        else if (isalpha(c)) {
            // Handle variables
            std::string varName;
            while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                varName += expression[i];
                i++;
            }
            i--;
            
            if (variableExists(varName)) {
                postfix << getVariable(varName) << ' ';
            } else {
                throw std::invalid_argument("Unknown variable: " + varName);
            }
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            if (operators.empty()) {
                throw std::invalid_argument("Mismatched parentheses");
            }
            operators.pop(); // Remove '('
        }
        else if (isOperator(c)) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(c);
        }
        else {
            throw std::invalid_argument("Invalid character: " + std::string(1, c));
        }
    }
    
    while (!operators.empty()) {
        if (operators.top() == '(') {
            throw std::invalid_argument("Mismatched parentheses");
        }
        postfix << operators.top() << ' ';
        operators.pop();
    }
    
    return postfix.str();
}

double Calculator::evaluatePostfix(const std::string& postfix) {
    std::stack<double> values;
    std::stringstream ss(postfix);
    std::string token;
    
    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
            values.push(std::stod(token));
        }
        else if (isOperator(token[0])) {
            if (values.size() < 2) {
                throw std::invalid_argument("Invalid expression");
            }
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOperation(a, b, token[0]));
        }
        else {
            throw std::invalid_argument("Invalid token: " + token);
        }
    }
    
    if (values.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }
    return values.top();
}

void Calculator::removeSpaces(std::string& str) const {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

bool Calculator::isValidExpression(const std::string& expression) const {
    int count = 0;
    for (char c : expression){
        if (c == '(') count++;
        else if (c == ')') count--;
        if (count < 0) return false;
    }
    return count == 0;
}

void Calculator::setVariable(const std::string &name, double value) {
    variables[name] = value;
}

double Calculator::getVariable(const std::string &name) const {
    auto it = variables.find(name);
    if (it != variables.end()) return it->second;
    throw std::invalid_argument("Variable not found");
}

bool Calculator::variableExists(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void Calculator::clearVariable() {
    variables.clear();
    variables["PI"] = 3.141592653;
    variables["E"] = 2.71828182845;
}

void Calculator::displayHelp() const {
    std::cout << "=== Calculator Help ===" << std::endl;
    std::cout << "Supported operations: +, -, *, /, ^" << std::endl;
    std::cout << "Predefined variables: PI, E" << std::endl;
    std::cout << "Set variables: x = 5" << std::endl;
    std::cout << "Examples: 2+3*4, (1+2)*3, PI*2" << std::endl;
    std::cout << "======================" << std::endl;
}
