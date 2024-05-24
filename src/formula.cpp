#include "parser/lexer.h"
#include "parser/parser.h"
#include "vm/bytecodeCompiler.h"
#include "vm/bytecodeInterpreter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Usage:
//   1. Read an expression from stdin
//      $ echo '1 + 1' | formula
//        2
//   2. Read an expression from a file
//      $ echo '1 + 1' > formula-test
//      $ formula ./formula-test
//        2

int main(int argc, char* argv[])
{
    bool useJIT = false;
    std::string expression;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--useJIT")
            useJIT = true;
        else {
            std::ifstream file(argv[i]);
            if (file.is_open()) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                expression = buffer.str();
            }
        }
    }

    if (expression.empty())
        std::getline(std::cin, expression);

    formula::Lexer lexer(expression);
    auto tokens = lexer.tokenize();

    formula::Parser parser(tokens);
    auto ast = parser.parse();

    formula::BytecodeCompiler compiler;
    auto bytecode = compiler.compile(ast);

    if (useJIT) {
        std::cout << "JIT Compiler hasn't been implemented yet" << std::endl;
    } else {
        formula::BytecodeInterpreter interpreter;
        double result = interpreter.execute(bytecode);
        std::cout << result << std::endl;
    }

    return 0;
}
