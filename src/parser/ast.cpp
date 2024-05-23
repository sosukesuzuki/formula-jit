#include "ast.h"
#include <iostream>

namespace formula {
NumberNode::NumberNode(double value)
    : value(value)
{
}
void NumberNode::print() const
{
    std::cout << value;
}

BinaryOpNode::BinaryOpNode(std::unique_ptr<ASTNode> left, char op, std::unique_ptr<ASTNode> right)
    : left(std::move(left))
    , right(std::move(right))
    , op(op)
{
}
void BinaryOpNode::print() const
{
    left->print();
    std::cout << " " << op << " ";
    right->print();
}
} // formula
