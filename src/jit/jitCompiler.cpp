#include "jitCompiler.h"
#include "../external/xbyak/xbyak.h"
#include "../vm/bytecodeCompiler.h"
#include <cstring>
#include <fstream>

namespace formula {

JITCompiler::JITCompiler()
    : CodeGenerator(4096)
{
}

JITCompiler::Func JITCompiler::compile(const BytecodeProgram& program)
{
    using namespace Xbyak;

    const uint8_t* ip = program.data();

    while (true) {
        Bytecode opcode = static_cast<Bytecode>(*ip++);
        switch (opcode) {
        case Bytecode::Push: {
            double* value = new double;
            std::memcpy(value, ip, sizeof(double));
            ip += sizeof(double);

            mov(rax, (size_t)value);
            movsd(xmm0, ptr[rax]);
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
            movsd(xmm1, ptr[rsp]);
            add(rsp, 8);
            movsd(xmm0, ptr[rsp]);
            subsd(xmm0, xmm1);
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
            movsd(xmm1, ptr[rsp]);
            add(rsp, 8);
            movsd(xmm0, ptr[rsp]);
            divsd(xmm0, xmm1);
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

} // namespace formula
