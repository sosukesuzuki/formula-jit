#pragma once

#include "../external/xbyak/xbyak.h"
#include "../vm/bytecodeCompiler.h"

namespace formula {

using namespace Xbyak;

class JITCompiler : public CodeGenerator {
public:
    typedef double (*Func)();
    JITCompiler();
    Func compile(const BytecodeProgram& program);
};

} // formula
