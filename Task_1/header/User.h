#pragma once

#include <string>
#include <vector>

class Group;

class User {
 private:
  uint32_t id;
  std::string name;
  Group* group;

 public:
  User(uint32_t UserId, std::string Name = "");

  bool SetName(std::string NewName);
  void SetGroup(Group* Group);
  std::string GetName() const;
  Group* GetGroup() const;
  uint32_t GetId() const;
};
