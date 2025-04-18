#include <type_traits>

namespace TypeListDetails {

template <typename... Types>
struct TypeList {};

template <std::size_t Index, typename List>
struct TypeAt;

template <std::size_t Index, typename Head, typename... Tail>
struct TypeAt<Index, TypeList<Head, Tail...>> {
  using type = typename TypeAt<Index - 1, TypeList<Tail...>>::type;
};

template <typename Head, typename... Tail>
struct TypeAt<0, TypeList<Head, Tail...>> {
  using type = Head;
};

template <typename List>
struct Size;

template <typename... Types>
struct Size<TypeList<Types...>> {
  static constexpr std::size_t value = sizeof...(Types);
};

template <typename T, typename List>
struct Contains;

template <typename T>
struct Contains<T, TypeList<>> {
  static constexpr bool value = false;
};

template <typename T, typename Head, typename... Tail>
struct Contains<T, TypeList<Head, Tail...>> {
  static constexpr bool value =
      std::is_same_v<T, Head> || Contains<T, TypeList<Tail...>>::value;
};

template <typename T, typename List, std::size_t Index = 0>
struct IndexOf;

template <typename T, typename... Tail, std::size_t Index>
struct IndexOf<T, TypeList<T, Tail...>, Index> {
  static constexpr std::size_t value = Index;
};

template <typename T, typename Head, typename... Tail, std::size_t Index>
struct IndexOf<T, TypeList<Head, Tail...>, Index> {
  static constexpr std::size_t value =
      IndexOf<T, TypeList<Tail...>, Index + 1>::value;
};

template <typename T, std::size_t Index>
struct IndexOf<T, TypeList<>, Index> {
  static_assert(sizeof(T) != sizeof(T), "Type not found in TypeList");
};

template <typename T, typename List>
struct Append;

template <typename T, typename... Types>
struct Append<T, TypeList<Types...>> {
  using type = TypeList<Types..., T>;
};

template <typename T, typename List>
struct Prepend;

template <typename T, typename... Types>
struct Prepend<T, TypeList<Types...>> {
  using type = TypeList<T, Types...>;
};

}  // namespace TypeListDetails

// Interface
template <typename... Types>
using TypeList = TypeListDetails::TypeList<Types...>;

template <std::size_t Index, typename List>
using TypeAt = typename TypeListDetails::TypeAt<Index, List>::type;

template <typename List>
constexpr std::size_t Size = TypeListDetails::Size<List>::value;

template <typename T, typename List>
constexpr bool Contains = TypeListDetails::Contains<T, List>::value;

template <typename T, typename List>
constexpr std::size_t IndexOf = TypeListDetails::IndexOf<T, List>::value;

template <typename T, typename List>
using Append = typename TypeListDetails::Append<T, List>::type;

template <typename T, typename List>
using Prepend = typename TypeListDetails::Prepend<T, List>::type;

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
