#pragma once

template <typename CountedType>
class counter {
 protected:
  counter() { ++count_; }
  counter(const counter&) { ++count_; }
  counter(counter&&) { ++count_; }
  ~counter() { --count_; }

 public:
  static size_t count() { return count_; }

 private:
  static inline size_t count_ = 0;
};
