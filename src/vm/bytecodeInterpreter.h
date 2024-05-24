#pragma once

#include "bytecodeCompiler.h"

namespace formula {

class BytecodeInterpreter {
public:
    double execute(const formula::BytecodeProgram& program);
};

} // formula
