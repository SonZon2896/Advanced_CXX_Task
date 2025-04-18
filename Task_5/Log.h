#pragma once

#include <algorithm>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ENTRIES 10

enum LogLevel {
  Note,
  Warning,
  Error,
};

class Log {
 private:
  Log() = default;

  static Log* instance;

  struct LogEntry {
    std::time_t time;
    LogLevel level;
    std::string message;
  };

  std::vector<LogEntry> entries;

 public:
  Log(const Log&) = delete;
  Log& operator=(const Log&) = delete;

  static Log* Instance();

  void AddMessage(LogLevel Level, const std::string& LogMessage);
  void PrintLastLogs() const;
};
