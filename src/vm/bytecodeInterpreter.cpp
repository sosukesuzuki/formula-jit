#include "bytecodeInterpreter.h"
#include "bytecodeCompiler.h"
#include <cstring>
#include <stdexcept>

namespace formula {

double BytecodeInterpreter::execute(const formula::BytecodeProgram& program)
{
    const uint8_t* ip = program.data();
    std::vector<double> stack;

    while (true) {
        Bytecode opcode = static_cast<Bytecode>(*ip++);
        switch (opcode) {
        case formula::Bytecode::Push: {
            double value;
            std::memcpy(&value, ip, sizeof(double));
            stack.push_back(value);
            ip += sizeof(double);
            break;
        }
        case formula::Bytecode::Add: {
            double b = stack.back();
            stack.pop_back();
            double a = stack.back();
            stack.pop_back();
            stack.push_back(a + b);
            break;
        }
        case formula::Bytecode::Sub: {
            double b = stack.back();
            stack.pop_back();
            double a = stack.back();
            stack.pop_back();
            stack.push_back(a - b);
            break;
        }
        case formula::Bytecode::Mul: {
            double b = stack.back();
            stack.pop_back();
            double a = stack.back();
            stack.pop_back();
            stack.push_back(a * b);
            break;
        }
        case formula::Bytecode::Div: {
            double b = stack.back();
            stack.pop_back();
            double a = stack.back();
            stack.pop_back();
            stack.push_back(a / b);
            break;
        }
        case formula::Bytecode::End:
            return stack.back();
        default:
            throw std::runtime_error("Unknown bytecode");
        }
    }
}

} // formula
