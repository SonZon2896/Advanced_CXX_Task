#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

#include "ExpressionFactory.h"

int main() {
  ExpressionFactory factory;

  Constant* c = factory.createConstant(2);
  Variable* v = factory.createVariable("x");
  Addition* expression = new Addition(c, v);

  map<string, double> context;
  context["x"] = 3;

  cout << "Expression: ";
  expression->print();
  cout << endl;
  cout << "Result: " << expression->calculate(context) << endl;

  delete expression;

  return 0;
}
