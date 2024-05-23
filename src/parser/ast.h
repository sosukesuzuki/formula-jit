#include <memory>

namespace formula {

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;
};

class NumberNode : public ASTNode {
public:
    double value;
    NumberNode(double value);
    void print() const override;
};

class BinaryOpNode : public ASTNode {
public:
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    char op;

    BinaryOpNode(std::unique_ptr<ASTNode> left, char op, std::unique_ptr<ASTNode> right);
    void print() const override;
};

} // formula
