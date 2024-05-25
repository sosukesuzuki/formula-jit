#include "jit/jitCompiler.h"
#include "parser/lexer.h"
#include "parser/parser.h"
#include "vm/bytecodeCompiler.h"
#include "vm/bytecodeInterpreter.h"
#include <fstream>
#include <iostream>
#include <regex>
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
    int repeated = 1;
    std::string expression;

    for (int i = 1; i < argc; ++i) {
        std::string arg = std::string(argv[i]);
        if (arg == "--useJIT")
            useJIT = true;
        else if (arg.starts_with("--repeated=")) {
            std::regex pattern(R"(--repeated=(\d+))");
            std::smatch matches;
            if (std::regex_match(arg, matches, pattern))
                repeated = std::stoi(matches[1].str());
        } else {
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
        formula::JITCompiler compiler;
        formula::JITCompiler::Func fn = compiler.compile(bytecode);
        double result = 0;
        for (int i = 0; i < repeated; i++)
            result += fn();
        std::cout << result << std::endl;
    } else {
        formula::BytecodeInterpreter interpreter;
        double result = 0;
        for (int i = 0; i < repeated; i++)
            result += interpreter.execute(bytecode);
        std::cout << result << std::endl;
    }

    return 0;
}
