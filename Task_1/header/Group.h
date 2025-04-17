#pragma once

#include <vector>

class User;

class Group {
  uint32_t id;
  std::vector<User*> users;

 public:
  Group(uint32_t GroupId);

  bool AddUser(User* NewUser);
  bool DeleteUser(User* DeleteUser);
  const std::vector<User*> GetUsers() const;
  uint32_t GetId() const;
};
