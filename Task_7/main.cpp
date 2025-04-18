#include "Set.h"

int main() {
  Set set1;

  for (int i = 1; i <= 5; ++i) {
    set1.Add(i);
  }
  std::cout << "Set1 (array impl): ";
  set1.Print();

  for (int i = 6; i <= 15; ++i) {
    set1.Add(i);
  }
  std::cout << "Set1 (hash impl): ";
  set1.Print();

  Set set2;
  for (int i = 10; i <= 20; ++i) {
    set2.Add(i);
  }
  std::cout << "Set2: ";
  set2.Print();

  Set unionSet = set1.UnionWith(set2);
  std::cout << "Union: ";
  unionSet.Print();

  Set intersectionSet = set1.IntersectionWith(set2);
  std::cout << "Intersection: ";
  intersectionSet.Print();

  for (int i = 1; i <= 10; ++i) {
    set1.Remove(i);
  }
  std::cout << "Set1 after removal: ";
  set1.Print();

  return 0;
}
