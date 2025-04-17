#include "../header/User.h"

User::User(uint32_t UserId, std::string Name) {
  id = UserId;
  group = nullptr;
  if (Name == "") {
    name = "User_" + std::to_string(id);
  } else {
    name = Name;
  }
}

bool User::SetName(std::string NewName) {
  if (!NewName.empty()) {
    name = NewName;
    return true;
  }
  return false;
}

void User::SetGroup(Group* NewGroup) { group = NewGroup; }

std::string User::GetName() const { return name; }
Group* User::GetGroup() const { return group; }
uint32_t User::GetId() const { return id; }
