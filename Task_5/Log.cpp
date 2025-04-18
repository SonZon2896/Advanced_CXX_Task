#include "Log.h"

Log* Log::instance = new Log();

Log* Log::Instance() { return Log::instance; }

void Log::AddMessage(LogLevel Level, const std::string& LogMessage) {
  LogEntry entry{std::time(nullptr), Level, LogMessage};

  entries.push_back(entry);

  // Ограничиваем размер лога
  if (entries.size() > MAX_ENTRIES) {
    entries.erase(entries.begin());
  }
}

void Log::PrintLastLogs() const {
  std::cout << "=== Last " << MAX_ENTRIES << " log entries ===" << std::endl;

  for (auto entry : entries) {
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S",
                  std::localtime(&entry.time));

    std::string levelStr;
    switch (entry.level) {
      case Note:
        levelStr = "Note";
        break;
      case Warning:
        levelStr = "Warning";
        break;
      case Error:
        levelStr = "Error";
        break;
    }

    // Выводим запись
    std::cout << "[" << timeStr << "] " << levelStr << ": " << entry.message
              << std::endl;
  }

  std::cout << "==========================" << std::endl;
}
