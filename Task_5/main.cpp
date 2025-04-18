#include "Log.h"

int main() {
  Log* log = Log::Instance();

  log->AddMessage(Note, "Program loaded");
  log->AddMessage(Warning, "Configuration file not found, using defaults");
  log->AddMessage(Note, "Initialization complete");
  log->AddMessage(Error, "Failed to connect to database");
  log->AddMessage(Note, "User logged in");
  log->AddMessage(Warning, "Disk space running low");
  log->AddMessage(Note, "Processing data");
  log->AddMessage(Error, "Critical error in module X");
  log->AddMessage(Note, "Saving results");
  log->AddMessage(Warning, "Network latency detected");
  log->AddMessage(Note, "Shutting down");
  log->AddMessage(Error, "Error happens! Help me!");

  log->PrintLastLogs();

  return 0;
}
