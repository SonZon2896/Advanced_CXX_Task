#include "ExpressionFactory.h"

void ExpressionFactory::createPredefinedConstants() {
  for (int i = -1; i <= 256; ++i) {
    Constant* c = new Constant(i);
    constantsPool[i] = c;
    precreatedConstants.push_back(c);
  }
}

ExpressionFactory::~ExpressionFactory() {
  // ”дал€ем все переменные
  for (auto& pair : variablesPool) {
    delete pair.second;
  }
  variablesPool.clear();

  // ”дал€ем только не предопределенные константы
  for (auto& pair : constantsPool) {
    // ѕровер€ем, не €вл€етс€ ли константа предопределенной
    if (pair.first < -1 || pair.first > 256) {
      delete pair.second;
    }
  }
  constantsPool.clear();

  for (auto c : precreatedConstants) {
    delete c;
  }
  precreatedConstants.clear();
}

Constant* ExpressionFactory::createConstant(double value) {
  auto it = constantsPool.find(value);
  if (it != constantsPool.end()) {
    return it->second;
  }

  Constant* c = new Constant(value);
  constantsPool[value] = c;
  return c;
}

Variable* ExpressionFactory::createVariable(const std::string& name) {
  auto it = variablesPool.find(name);
  if (it != variablesPool.end()) {
    return it->second;
  }

  Variable* v = new Variable(name);
  variablesPool[name] = v;
  return v;
}
