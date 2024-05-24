#pragma once

#include "parser/ast.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace formula {

enum class Bytecode : uint8_t {
    Push,
    Add,
    Sub,
    Mul,
    Div,
    End
};

using BytecodeProgram = std::vector<uint8_t>;

class BytecodeCompiler {
public:
    BytecodeProgram compile(const std::unique_ptr<formula::ASTNode>& node, BytecodeProgram& program);

private:
    void compile_node(const std::unique_ptr<ASTNode>& node, BytecodeProgram& program);
};

} // formula
