#include "bytecodeCompiler.h"
#include <stdexcept>

namespace formula {

formula::BytecodeProgram BytecodeCompiler::compile(const std::unique_ptr<formula::ASTNode>& node)
{
    BytecodeProgram program;
    compile_node(node, program);
    program.push_back(static_cast<uint8_t>(Bytecode::End));
    return program;
}

void BytecodeCompiler::compile_node(const std::unique_ptr<ASTNode>& node, BytecodeProgram& program)
{
    if (const auto* num_node = dynamic_cast<const NumberNode*>(node.get())) {
        program.push_back(static_cast<uint8_t>(Bytecode::Push));
        double value = num_node->value;
        auto ptr = reinterpret_cast<const uint8_t*>(&value);
        program.insert(program.end(), ptr, ptr + sizeof(double));
    } else if (const auto* bin_op_node = dynamic_cast<const BinaryOpNode*>(node.get())) {
        compile_node(bin_op_node->left, program);
        compile_node(bin_op_node->right, program);
        switch (bin_op_node->op) {
        case '+':
            program.push_back(static_cast<uint8_t>(Bytecode::Add));
            break;
        case '-':
            program.push_back(static_cast<uint8_t>(Bytecode::Sub));
            break;
        case '*':
            program.push_back(static_cast<uint8_t>(Bytecode::Mul));
            break;
        case '/':
            program.push_back(static_cast<uint8_t>(Bytecode::Div));
            break;
        default:
            throw std::runtime_error("Unknown operator");
        }
    } else {
        throw std::runtime_error("Unknown AST node type");
    }
}

} // formula
