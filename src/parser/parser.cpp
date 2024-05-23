#include "parser.h"
#include "lexer.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace formula {

Parser::Parser(const std::vector<formula::Token>& tokens)
    : tokens(tokens)
    , pos(0)
{
}

std::unique_ptr<formula::ASTNode> Parser::parse()
{
    return expr();
}

const formula::Token& Parser::current_token() const
{
    return tokens[pos];
}

void Parser::advance()
{
    pos++;
}

std::unique_ptr<formula::ASTNode> Parser::factor()
{
    const formula::Token& token = current_token();
    if (token.type == formula::TokenType::Number) {
        advance();
        return std::make_unique<NumberNode>(token.value);
    } else if (token.type == formula::TokenType::LParen) {
        advance();
        auto node = expr();
        if (current_token().type != formula::TokenType::RParen)
            throw std::runtime_error("Expected ')'");
        advance();
        return node;
    } else
        throw std::runtime_error("Expected number or '('");
}

std::unique_ptr<formula::ASTNode> Parser::term()
{
    auto node = factor();
    while (current_token().type == formula::TokenType::Mul || current_token().type == formula::TokenType::Div) {
        char op = (current_token().type == formula::TokenType::Mul) ? '*' : '/';
        advance();
        node = std::make_unique<formula::BinaryOpNode>(std::move(node), op, factor());
    }
    return node;
}

std::unique_ptr<ASTNode> Parser::expr()
{
    auto node = term();
    while (current_token().type == formula::TokenType::Plus || current_token().type == formula::TokenType::Minus) {
        char op = (current_token().type == formula::TokenType::Plus) ? '+' : '-';
        advance();
        node = std::make_unique<BinaryOpNode>(std::move(node), op, term());
    }
    return node;
}

} // formula
