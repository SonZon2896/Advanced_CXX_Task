#pragma once

#include <map>
#include <string>

class Expression {
 public:
  virtual ~Expression() = default;
  virtual double calculate(
      const std::map<std::string, double>& context) const = 0;
  virtual void print() const = 0;
  virtual bool isShared() const = 0;
};
