#include <cassert>
#include <iostream>

#include "counter.h"
#include "less_than_comparable.h"

class Number : public less_than_comparable<Number>, public counter<Number> {
 public:
  Number(int value) : mValue{value} {}

  int value() const { return mValue; }

  bool operator<(const Number& other) const { return mValue < other.mValue; }

 private:
  int mValue;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};

  assert(one >= one);
  assert(three <= four);
  assert(two == two);
  assert(three > two);
  assert(one < two);
  assert(one != two);

  // Проверка счетчика
  std::cout << "Count: " << counter<Number>::count() << std::endl;
  {
    Number five{5};
    std::cout << "Count after creating five: " << counter<Number>::count()
              << std::endl;
  }
  std::cout << "Count after five destroyed: " << counter<Number>::count()
            << std::endl;

  return 0;
}
