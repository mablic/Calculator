# C++ Calculator Project

A command-line calculator that supports basic arithmetic operations, mathematical constants, and user-defined variables.

## Features

- Basic arithmetic operations: `+`, `-`, `*`, `/`, `^` (exponentiation)
- Built-in mathematical constants: `PI`, `E`
- User-defined variables
- Expression evaluation with proper operator precedence
- Parentheses support for complex expressions

## Building

This project uses a Makefile for building. Make sure you have `g++` installed with C++17 support.

### Build Commands

```bash
# Build the project
make

# Build and run
make run

# Clean build artifacts
make clean

# Build debug version
make debug

# Build optimized release version
make release
```

## Usage

After building, run the calculator:

```bash
./build/calculator
```

### Example Expressions

```bash
2+3          # Addition: 5
2*3+4        # Multiplication with addition: 10
PI*2         # Using built-in constants: 6.28319
(1+2)*3      # Parentheses: 9
2^3          # Exponentiation: 8
```

### Setting Variables

The calculator supports user-defined variables:

```cpp
Calculator calc;
calc.setVariable("x", 5.0);
// Now you can use 'x' in expressions
```

## Project Structure

- `main.cpp` - Entry point and demonstration code
- `Calculator.cpp` - Calculator implementation
- `Calculator.hpp` - Calculator class definition
- `Makefile` - Build configuration
- `support.cpp` - Additional utility functions (not used in main build)

## Requirements

- C++17 compatible compiler (g++, clang++)
- Standard C++ libraries

## Implementation Details

The calculator uses the shunting yard algorithm to convert infix notation to postfix notation, then evaluates the postfix expression using a stack-based approach.
