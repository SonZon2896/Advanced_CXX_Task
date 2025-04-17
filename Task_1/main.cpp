#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "header/Group.h"
#include "header/User.h"

inline static uint32_t static_user_id = 0;
inline static uint32_t static_group_id = 0;

inline static std::vector<User*> all_users;
inline static std::vector<Group*> all_groups;

void CreateUser(std::string UserName = "") {
  User* new_user = new User(static_user_id++, UserName);
  all_users.push_back(new_user);
}

void CreateGroup() {
  Group* new_group = new Group(static_group_id++);
  all_groups.push_back(new_group);
}

bool DeleteUser(uint32_t UserId) {
  for (auto user = all_users.begin(); user != all_users.end(); ++user) {
    if ((*user)->GetId() == UserId) {
      if ((*user)->GetGroup()) {
        (*user)->GetGroup()->DeleteUser((*user));
      }
      all_users.erase(user);
      return true;
    } else if ((*user)->GetId() > UserId) {
      return false;
    }
  }
  return false;
}

bool DeleteGroup(uint32_t GroupId) {
  for (auto group = all_groups.begin(); group != all_groups.end(); ++group) {
    if ((*group)->GetId() == GroupId) {
      for (auto user : (*group)->GetUsers()) {
        user->SetGroup(nullptr);
      }
      all_groups.erase(group);
      return true;
    } else if ((*group)->GetId() > GroupId) {
      return false;
    }
  }
  return false;
}

User* GetUserById(uint32_t UserId) {
  for (auto user : all_users) {
    if (user->GetId() == UserId) {
      return user;
    }
  }
  return nullptr;
}

Group* GetGroupById(uint32_t GroupId) {
  for (auto group : all_groups) {
    if (group->GetId() == GroupId) {
      return group;
    }
  }
  return nullptr;
}

bool AddUserToGroup(uint32_t UserId, uint32_t GroupId) {
  auto user = GetUserById(UserId);
  auto group = GetGroupById(GroupId);
  if (user && group) {
    if (user->GetGroup()) {
      user->GetGroup()->DeleteUser(user);
    }
    group->AddUser(user);
    user->SetGroup(group);
    return true;
  } else {
    return false;
  }
}

bool DeleteUserFromGroup(uint32_t UserId, uint32_t GroupId) {
  auto user = GetUserById(UserId);
  auto group = GetGroupById(GroupId);
  if (user && group) {
    group->DeleteUser(user);
    user->SetGroup(nullptr);
    return true;
  } else {
    return false;
  }
}

void PrintUser(User* PrintUser, bool isAllUsers = false) {
  if (!isAllUsers) {
    printf("\n");
  }
  printf("User: name{%s}, id{%d}, group{%d}\n", PrintUser->GetName().c_str(),
         PrintUser->GetId(),
         PrintUser->GetGroup() ? PrintUser->GetGroup()->GetId() : -1);
  if (!isAllUsers) {
    printf("\n");
  }
}

void PrintGroup(Group* PrintGroup, bool isAllGroups = false) {
  if (!isAllGroups) {
    printf("\n");
  }
  printf("Group: id{%d}, users(%d):\n", PrintGroup->GetId(),
         PrintGroup->GetUsers().size());
  for (auto user : PrintGroup->GetUsers()) {
    printf("\t");
    if (isAllGroups) {
      printf("\t");
    }
    PrintUser(user, true);
  }
  if (!isAllGroups) {
    printf("\n");
  }
}

void PrintAllUsers() {
  printf("\n");
  for (auto user : all_users) {
    printf("\t");
    PrintUser(user, true);
  }
  printf("\n");
}

void PrintAllGroups() {
  printf("\n");
  for (auto group : all_groups) {
    printf("\t");
    PrintGroup(group, true);
  }
  printf("\n");
}

void Exit() {
  for (auto user : all_users) {
    delete user;
  }
  for (auto group : all_groups) {
    delete group;
  }
  exit(0);
}

void Help() {
  printf(
      "* createUser {username} - create new user\n"
      "* deleteUser {userId} - delete user\n"
      "* allUsers - print all users\n"
      "* getUser {userId} - print user\n"
      "* createGroup - create Group\n"
      "* deleteGroup {groupId} - delete Group\n"
      "* allGroups - print all groups\n"
      "* getGroup {groupId} - print Group\n"
      "* addUserToGroup {userId} {groupId}\n"
      "* deleteUserFromGroup {userId} {groupId}\n\n");
}

void ExecuteCommand(std::string Command) {
  std::istringstream ss(Command);
  std::string command;
  ss >> command;
  if (command == "createUser") {
    std::string name;
    if (ss >> name) {
      CreateUser(name);
    } else {
      CreateUser();
    }
  } else if (command == "deleteUser") {
    uint32_t user_id;
    if (ss >> user_id) {
      DeleteUser(user_id);
    }
  } else if (command == "allUsers") {
    PrintAllUsers();
  } else if (command == "getUser") {
    uint32_t user_id;
    if (ss >> user_id) {
      PrintUser(GetUserById(user_id));
    }
  } else if (command == "createGroup") {
    CreateGroup();
  } else if (command == "deleteGroup") {
    uint32_t group_id;
    if (ss >> group_id) {
      DeleteGroup(group_id);
    }
  } else if (command == "allGroups") {
    PrintAllGroups();
  } else if (command == "getGroup") {
    uint32_t group_id;
    if (ss >> group_id) {
      PrintGroup(GetGroupById(group_id));
    }
  } else if (command == "addUserToGroup") {
    uint32_t user_id, group_id;
    if (ss >> user_id && ss >> group_id) {
      AddUserToGroup(user_id, group_id);
    }
  } else if (command == "deleteUserFromGroup") {
    uint32_t user_id, group_id;
    if (ss >> user_id && ss >> group_id) {
      DeleteUserFromGroup(user_id, group_id);
    }
  } else if (command == "exit") {
    Exit();
  } else if (command == "help") {
    Help();
  } else {
    printf("Unknown command\n");
  }
}

int main() {
  while (true) {
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command);
    ExecuteCommand(command);
  }
}
