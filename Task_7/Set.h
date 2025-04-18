#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>

#define ARRAY_THRESHOLD 10

class SetAbstract {
 public:
  virtual ~SetAbstract() = default;
  virtual void Add(int Element) = 0;
  virtual void Remove(int Element) = 0;
  virtual bool Contains(int Element) const = 0;
  virtual std::vector<int> GetElements() const = 0;
  virtual uint32_t Size() const = 0;
  virtual SetAbstract* Clone() const = 0;
};

class ArraySetImpl : public SetAbstract {
 private:
  std::vector<int> elements;

 public:
  void Add(int Element) override;
  void Remove(int Element) override;
  bool Contains(int Element) const override;
  std::vector<int> GetElements() const override;
  uint32_t Size() const override;
  SetAbstract* Clone() const override;
};

class HashSetImpl : public SetAbstract {
 private:
  std::unordered_set<int> elements;

 public:
  void Add(int Element) override;
  void Remove(int Element) override;
  bool Contains(int Element) const override;
  std::vector<int> GetElements() const override;
  uint32_t Size() const override;
  SetAbstract* Clone() const override;
};

class Set {
 public:
  Set();

  void Add(int element);
  void Remove(int element);
  bool Contains(int element) const;
  uint32_t Size() const;

  Set UnionWith(const Set& other) const;
  Set IntersectionWith(const Set& other) const;

  void Print() const;

 private:
  SetAbstract* implementation;

  void CheckAndMigrate();
};
