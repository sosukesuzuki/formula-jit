#include "parser/lexer.h"
#include "parser/parser.h"
#include "vm/bytecodeCompiler.h"
#include "vm/bytecodeInterpreter.h"
#include <iostream>
#include <string>

int main()
{
    std::string expression = "3 + 5 * (10 - 2)";

    formula::Lexer lexer(expression);
    auto tokens = lexer.tokenize();

    formula::Parser parser(tokens);
    auto ast = parser.parse();

    formula::BytecodeCompiler compiler;
    auto bytecode = compiler.compile(ast);

    formula::BytecodeInterpreter interpreter;
    double result = interpreter.execute(bytecode);

    std::cout << result << std::endl;

    return 0;
}
