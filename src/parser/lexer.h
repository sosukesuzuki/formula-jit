#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace formula {
enum class TokenType {
    Number,
    Plus,
    Minus,
    Mul,
    Div,
    LParen,
    RParen,
    End
};

struct Token {
    TokenType type;
    double value; // Only used for numbers
};

class Lexer {
    const std::string& text;
    size_t pos;
    char current_char;

public:
    Lexer(const std::string& text);
    void advance();
    std::vector<Token> tokenize();

private:
    double number();
};
} // formula
