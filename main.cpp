#include "Calculator.hpp"
#include <iostream>

int main() {
    Calculator calc;
    
    try {
        std::cout << "2+3 = " << calc.Calculate("2+3") << std::endl;
        std::cout << "PI = " << calc.Calculate("PI") << std::endl;
        std::cout << "2*3+4 = " << calc.Calculate("2*3+4") << std::endl;
        
        calc.setVariable("x", 5.0);
        std::cout << "x+3 = " << calc.Calculate("x+3") << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
