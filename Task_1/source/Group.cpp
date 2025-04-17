#include "../header/Group.h"

Group::Group(uint32_t GroupId) { id = GroupId; }

bool Group::AddUser(User* NewUser) {
  if (std::find(users.begin(), users.end(), NewUser) == users.end()) {
    users.push_back(NewUser);
    return true;
  }
  return false;
}

bool Group::DeleteUser(User* DeleteUser) {
  auto it = std::find(users.begin(), users.end(), DeleteUser);
  if (it != users.end()) {
    users.erase(it);
    return true;
  }
  return false;
}

const std::vector<User*> Group::GetUsers() const { return users; }
uint32_t Group::GetId() const { return id; }
