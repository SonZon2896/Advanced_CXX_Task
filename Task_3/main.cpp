#include <iostream>
#include <string>

#include "TypeMap.h"

struct DataA {
  std::string value;
};

struct DataB {
  int value;
};

int main() {
  TypeMap<KeyValuePair<int, int>, KeyValuePair<double, double>,
          KeyValuePair<DataA, DataA>, KeyValuePair<DataB, DataB> >
      myTypeMap;

  // Добавление элементов
  myTypeMap.AddValue<int>(42);
  myTypeMap.AddValue<double>(3.14);
  myTypeMap.AddValue<DataA>({"Hello, TypeMap!"});
  myTypeMap.AddValue<DataB>({10});

  // Получение значений
  std::cout << "int: " << myTypeMap.GetValue<int>() << std::endl;
  std::cout << "double: " << myTypeMap.GetValue<double>() << std::endl;
  std::cout << "DataA: " << myTypeMap.GetValue<DataA>().value << std::endl;
  std::cout << "DataB: " << myTypeMap.GetValue<DataB>().value << std::endl;

  // Проверка наличия
  std::cout << "Contains int? " << (myTypeMap.Contains<int>() ? "Yes" : "No")
            << std::endl;

  // Удаление элемента
  myTypeMap.RemoveValue<double>();
  std::cout << "Contains double after removal? "
            << (myTypeMap.Contains<double>() ? "Yes" : "No") << std::endl;

  return 0;
}
