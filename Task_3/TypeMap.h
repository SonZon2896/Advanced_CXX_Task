#pragma once
#include <array>
#include <stdexcept>
#include <tuple>

#include "TypeList.h"

template <typename Key, typename Value>
struct KeyValuePair {
  using KeyType = Key;
  using ValueType = Value;
};

template <typename... Pairs>
class TypeMap {
  static_assert(sizeof...(Pairs) > 0,
                "TypeMap must have at least one key-value pair");

  using KeyList = TypeList<typename Pairs::KeyType...>;
  using ValueList = TypeList<typename Pairs::ValueType...>;

  std::tuple<typename Pairs::ValueType...> values;
  std::array<bool, sizeof...(Pairs)> presenceFlags{};

  template <typename Key>
  using ValueTypeFor = TypeAt<IndexOf<Key, KeyList>, ValueList>;

 public:
  template <typename Key>
  void AddValue(ValueTypeFor<Key> value) {
    constexpr std::size_t index = IndexOf<Key, KeyList>;
    std::get<index>(values) = value;
    presenceFlags[index] = true;
  }

  template <typename Key>
  ValueTypeFor<Key>& GetValue() {
    constexpr std::size_t index = IndexOf<Key, KeyList>;
    if (!presenceFlags[index]) {
      throw std::runtime_error("Value not present in TypeMap");
    }
    return std::get<index>(values);
  }

  template <typename Key>
  const ValueTypeFor<Key>& GetValue() const {
    constexpr std::size_t index = IndexOf<Key, KeyList>;
    if (!presenceFlags[index]) {
      throw std::runtime_error("Value not present in TypeMap");
    }
    return std::get<index>(values);
  }

  template <typename Key>
  bool Contains() const {
    constexpr std::size_t index = IndexOf<Key, KeyList>;
    return presenceFlags[index];
  }

  template <typename Key>
  void RemoveValue() {
    constexpr std::size_t index = IndexOf<Key, KeyList>;
    presenceFlags[index] = false;
  }
};
