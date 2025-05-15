#pragma once

#include <unordered_map>
#include <vector>

#include "Addition.h"
#include "Constant.h"
#include "Expression.h"
#include "Operator.h"
#include "Variable.h"

class ExpressionFactory {
 private:
  std::unordered_map<double, Constant*> constantsPool;
  std::unordered_map<std::string, Variable*> variablesPool;
  std::vector<Constant*> precreatedConstants;

  // Создаем предопределенные константы (от -1 до 256)
  void createPredefinedConstants();

 public:
  ExpressionFactory() { createPredefinedConstants(); }
  ~ExpressionFactory();

  Constant* createConstant(double value);
  Variable* createVariable(const std::string& name);
};
