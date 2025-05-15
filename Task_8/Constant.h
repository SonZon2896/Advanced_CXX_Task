#pragma once

#include <iostream>

#include "Expression.h"

class Constant : public Expression {
 private:
  double value;
  Constant(double value) : value(value) {}
  Constant(const Constant&) = delete;
  Constant& operator=(const Constant&) = delete;

  friend class ExpressionFactory;

 public:
  double calculate(const std::map<std::string, double>&) const override {
    return value;
  }

  void print() const override { std::cout << value; }

  bool isShared() const override { return true; }
};
