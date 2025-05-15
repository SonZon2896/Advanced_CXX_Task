#pragma once

#include "Operator.h"

class Addition : public Operator {
 public:
  Addition(Expression* left, Expression* right) : Operator(left, right) {}

  double calculate(
      const std::map<std::string, double>& context) const override {
    return left->calculate(context) + right->calculate(context);
  }

  void print() const override {
    std::cout << "(";
    left->print();
    std::cout << " + ";
    right->print();
    std::cout << ")";
  }

  bool isShared() const override { return false; }
};
