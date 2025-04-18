#include "Set.h"

void ArraySetImpl::Add(int Element) {
  if (!Contains(Element)) {
    elements.push_back(Element);
  }
}

void ArraySetImpl::Remove(int Element) {
  elements.erase(std::remove(elements.begin(), elements.end(), Element),
                 elements.end());
}

bool ArraySetImpl::Contains(int Element) const {
  return std::find(elements.begin(), elements.end(), Element) != elements.end();
}

std::vector<int> ArraySetImpl::GetElements() const { return elements; }

uint32_t ArraySetImpl::Size() const { return elements.size(); }

SetAbstract* ArraySetImpl::Clone() const { return (SetAbstract*)(this); }

void HashSetImpl::Add(int Element) { elements.insert(Element); }

void HashSetImpl::Remove(int Element) { elements.erase(Element); }

bool HashSetImpl::Contains(int Element) const {
  return elements.find(Element) != elements.end();
}

std::vector<int> HashSetImpl::GetElements() const {
  return std::vector<int>(elements.begin(), elements.end());
}

uint32_t HashSetImpl::Size() const { return elements.size(); }

SetAbstract* HashSetImpl::Clone() const { return (SetAbstract*)(this); }

Set::Set() : implementation(new ArraySetImpl()) {}

void Set::Add(int Element) {
  CheckAndMigrate();
  implementation->Add(Element);
}

void Set::Remove(int Element) {
  implementation->Remove(Element);
  CheckAndMigrate();
}

bool Set::Contains(int Element) const {
  return implementation->Contains(Element);
}

uint32_t Set::Size() const { return implementation->Size(); }

Set Set::UnionWith(const Set& Other) const {
  Set result;
  auto elements = implementation->GetElements();
  for (int element : elements) {
    result.Add(element);
  }

  auto otherElements = Other.implementation->GetElements();
  for (int elem : otherElements) {
    result.Add(elem);
  }

  return result;
}

Set Set::IntersectionWith(const Set& Other) const {
  Set result;
  auto elements = implementation->GetElements();
  for (int element : elements) {
    if (Other.Contains(element)) {
      result.Add(element);
    }
  }
  return result;
}

void Set::Print() const {
  auto elements = implementation->GetElements();
  std::cout << "{ ";
  for (int elem : elements) {
    std::cout << elem << " ";
  }
  std::cout << "}" << std::endl;
}

void Set::CheckAndMigrate() {
  size_t currentSize = implementation->Size();

  if (currentSize > ARRAY_THRESHOLD &&
      dynamic_cast<ArraySetImpl*>(implementation)) {
    auto newImpl = new HashSetImpl();
    for (int element : implementation->GetElements()) {
      newImpl->Add(element);
    }
    delete implementation;
    implementation = newImpl;
  } else if (currentSize <= ARRAY_THRESHOLD &&
             dynamic_cast<HashSetImpl*>(implementation)) {
    auto newImpl = new ArraySetImpl();
    for (int element : implementation->GetElements()) {
      newImpl->Add(element);
    }
    delete implementation;
    implementation = newImpl;
  }
}
