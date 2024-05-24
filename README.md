# Formula JIT Interpreter

The Formula JIT Interpreter is an interpreter for evaluating arithmetic expressions consisting of arithmetic operations, parentheses, integers, and floating-point numbers.

## Architecture

1. Parse the given expression as a string and convert it to an Abstract Syntax Tree (AST).
2. Compile the AST into bytecode for a stack-based virtual machine.
3. If the `--useJIT` option is enabled:
    1. JIT compile the bytecode into x86_64 machine code using [Xbyak](https://github.com/herumi/xbyak).
    2. Execute the JIT-compiled result.
4. Otherwise:
    1. Execute the bytecode directly on a virtual machine implemented in C++.

## Usage

Clone the repository and build the project.

```
git clone https://github.com/sosukesuzuki/formula-jit.git
cd formula-jit
./scripts/build.sh
```

There are two ways to use the interpreter. The first is to evaluate expressions from standard input.

```
echo '1 + 1' | ./build/formula
```

The second is to pass a file path as a command-line argument to evaluate an expression.

```
echo '1 + 1' > expr
./build/formula ./expr
```

You can enable JIT compilation with the `--useJIT` command-line option.

```
echo '1 + 1' | ./build/formula --useJIT
```
