#include <type_traits>

#include "TypeList.h"

// Tests
int main() {
  using MyList = TypeList<int, double, char>;

  static_assert(std::is_same_v<TypeAt<0, MyList>, int>);
  static_assert(std::is_same_v<TypeAt<1, MyList>, double>);
  static_assert(std::is_same_v<TypeAt<2, MyList>, char>);

  static_assert(Size<MyList> == 3);

  static_assert(Contains<int, MyList>);
  static_assert(Contains<double, MyList>);
  static_assert(Contains<char, MyList>);
  static_assert(!Contains<float, MyList>);

  static_assert(IndexOf<int, MyList> == 0);
  static_assert(IndexOf<double, MyList> == 1);
  static_assert(IndexOf<char, MyList> == 2);

  using AppendedList = Append<float, MyList>;
  static_assert(std::is_same_v<TypeAt<3, AppendedList>, float>);
  static_assert(Size<AppendedList> == 4);

  using PrependedList = Prepend<float, MyList>;
  static_assert(std::is_same_v<TypeAt<0, PrependedList>, float>);
  static_assert(Size<PrependedList> == 4);

  return 0;
}
