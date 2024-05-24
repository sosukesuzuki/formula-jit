#include "lexer.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>

namespace formula {

Lexer::Lexer(const std::string& text)
    : text(text)
    , pos(0)
    , current_char(text[0])
{
}

void Lexer::advance()
{
    pos++;
    if (pos < text.length())
        current_char = text[pos];
    else
        current_char = '\0';
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (current_char != '\0') {
        if (isspace(current_char))
            advance();
        else if (isdigit(current_char)) {
            tokens.push_back({ TokenType::Number, number() });
        } else if (current_char == '+') {
            tokens.push_back({ TokenType::Plus, 0 });
            advance();
        } else if (current_char == '-') {
            tokens.push_back({ TokenType::Minus, 0 });
            advance();
        } else if (current_char == '*') {
            tokens.push_back({ TokenType::Mul, 0 });
            advance();
        } else if (current_char == '/') {
            tokens.push_back({ TokenType::Div, 0 });
            advance();
        } else if (current_char == '(') {
            tokens.push_back({ TokenType::LParen, 0 });
            advance();
        } else if (current_char == ')') {
            tokens.push_back({ TokenType::RParen, 0 });
            advance();
        } else {
            throw std::runtime_error("Invalid character");
        }
    }
    return tokens;
}

double Lexer::number()
{
    std::ostringstream result;
    while (isdigit(current_char) || current_char == '.') {
        result << current_char;
        advance();
    }
    return std::stod(result.str());
}

} // formlura
