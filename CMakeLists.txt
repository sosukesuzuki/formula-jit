cmake_minimum_required(VERSION 3.0)

project(Formula
        VERSION 1.0
        DESCRIPTION "The Formula Interpreter")

set(CMAKE_CXX_STANDARD 20)

add_executable(formula
               src/formula.cpp
               src/parser/ast.cpp
               src/parser/lexer.cpp
               src/parser/parser.cpp
               src/vm/bytecodeCompiler.cpp
               src/vm/bytecodeInterpreter.cpp
               src/jit/jitCompiler.cpp)

target_include_directories(formula PRIVATE src)
