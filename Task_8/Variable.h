#pragma once

#include <iostream>
#include <map>
#include <string>

#include "Expression.h"

class Variable : public Expression {
 private:
  std::string name;
  Variable(const std::string& name) : name(name) {}

  Variable(const Variable&) = delete;
  Variable& operator=(const Variable&) = delete;

  friend class ExpressionFactory;

 public:
  double calculate(
      const std::map<std::string, double>& context) const override {
    auto it = context.find(name);
    if (it != context.end()) {
      return it->second;
    }
    throw std::runtime_error("Variable " + name + " not found in context");
  }

  void print() const override { std::cout << name; }

  bool isShared() const override { return true; }
};
