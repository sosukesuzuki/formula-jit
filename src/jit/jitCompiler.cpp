#include "jitCompiler.h"
#include "../external/xbyak/xbyak.h"
#include "../vm/bytecodeCompiler.h"
#include <cstring>

namespace formula {

JITCompiler::JITCompiler()
    : CodeGenerator(4096)
{
}

JITCompiler::Func JITCompiler::compile(const BytecodeProgram& program)
{
    using namespace Xbyak;

    const uint8_t* ip = program.data();

    std::vector<double> stack;
    while (true) {
        Bytecode opcode = static_cast<Bytecode>(*ip++);
        switch (opcode) {
        case Bytecode::Push: {
            double value;
            std::memcpy(&value, ip, sizeof(double));
            ip += sizeof(double);
            mov(rax, (size_t)&value);
            sub(rsp, 8);
            movsd(ptr[rsp], xmm0);
            break;
        }
        case Bytecode::Add: {
            movsd(xmm0, ptr[rsp]);
            add(rsp, 8);
            addsd(xmm0, ptr[rsp]);
            movsd(ptr[rsp], xmm0);
            break;
        }
        case Bytecode::Sub: {
            movsd(xmm0, ptr[rsp]);
            add(rsp, 8);
            subsd(xmm0, ptr[rsp]);
            movsd(ptr[rsp], xmm0);
            break;
        }
        case Bytecode::Mul: {
            movsd(xmm0, ptr[rsp]);
            add(rsp, 8);
            mulsd(xmm0, ptr[rsp]);
            movsd(ptr[rsp], xmm0);
            break;
        }
        case Bytecode::Div: {
            movsd(xmm0, ptr[rsp]);
            add(rsp, 8);
            divsd(xmm0, ptr[rsp]);
            movsd(ptr[rsp], xmm0);
            break;
        }
        case Bytecode::End: {
            movsd(xmm0, ptr[rsp]);
            add(rsp, 8);
            ret();
            goto end;
        }
        default: {
            throw std::runtime_error("Unknown bytecode");
        }
        }
    }

end:
    JITCompiler::Func fn = getCode<JITCompiler::Func>();
    return fn;
}

} // formula
