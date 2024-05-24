#pragma once

#include "../external/xbyak/xbyak.h"
#include "../vm/bytecodeCompiler.h"
#include <vector>

namespace formula {

using namespace Xbyak;

class JITCompiler : public CodeGenerator {
public:
    typedef double (*Func)();
    JITCompiler();
    ~JITCompiler();
    Func compile(const BytecodeProgram& program);

private:
    std::vector<double*> allocatedValues;
};

} // formula
