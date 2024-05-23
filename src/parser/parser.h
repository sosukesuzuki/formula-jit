#include "ast.h"
#include "lexer.h"
#include <cstddef>
#include <memory>
#include <vector>

namespace formula {

class Parser {
    std::vector<formula::Token> tokens;
    size_t pos;

public:
    Parser(const std::vector<formula::Token>& tokens);
    std::unique_ptr<formula::ASTNode> parse();

private:
    const formula::Token& current_token() const;
    void advance();
    std::unique_ptr<formula::ASTNode> factor();
    std::unique_ptr<formula::ASTNode> term();
    std::unique_ptr<formula::ASTNode> expr();
};

} // formula
