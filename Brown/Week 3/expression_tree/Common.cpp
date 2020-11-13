#include <Common.h>
#include <memory>
#include <string>

class ValueExpression : public Expression {
private:
    int value_;
public:
    ValueExpression(int value) : value_(std::move(value)) { }

    int Evaluate() const final { return value_; }
    std::string ToString() const final { return std::to_string(value_); }
};

class OperationExpression : public Expression {
private:
    ExpressionPtr left_;
    ExpressionPtr right_;
    char operation_;
public:
    OperationExpression(char operation, 
                        ExpressionPtr left, ExpressionPtr right) 
                        : operation_(operation), left_(std::move(left)), right_(std::move(right)) { }

    int Evaluate() const final {
        if (operation_ == '+') {
            return left_->Evaluate() + right_->Evaluate();
        }
        return left_->Evaluate() * right_->Evaluate(); // *
    }
    std::string ToString() const final { return '(' + left_->ToString() + ')' + operation_ + '(' + right_->ToString() + ')' ; }
};

ExpressionPtr Value(int value) {
    return std::make_unique<ValueExpression>(std::move(value));
}
ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<OperationExpression>('+', std::move(left), std::move(right));
}
ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return std::make_unique<OperationExpression>('*', std::move(left), std::move(right));
}
