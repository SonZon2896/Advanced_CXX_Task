#pragma once

#include "Expression.h"

class Operator : public Expression {
 protected:
  Expression* left;
  Expression* right;

 public:
  Operator(Expression* left, Expression* right) : left(left), right(right) {}
  virtual ~Operator() {
    // Удаляем только не-разделяемые объекты
    if (left && !left->isShared()) delete left;
    if (right && !right->isShared()) delete right;
  }
};
