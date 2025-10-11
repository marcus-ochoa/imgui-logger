#pragma once

#include <vector>
#include <fstream>

enum LogLevel 
{
    INFO,
    WARN,
    ERROR,
};

struct Log
{
    const char* message;
    LogLevel level;
    double time;

    Log(): message("EMPTY LOG PASSED"), level(LogLevel::ERROR), time(0.0) {};
    Log(const char* m, LogLevel l, double t): message(m), level(l), time(t) {};
};


class Logger
{
public:
    static Logger& GetInstance();

    void Draw(bool *p_open);
    void AddLog(const char* message, LogLevel level);
    void SetEnabled(bool enabledState);
    bool GetEnabled() { return isEnabled; };

    ~Logger() { if (logFile.is_open()) { logFile.close(); } };

private:
    Logger() {}; // Hidden constructor for singleton

    bool isEnabled = true;

    const char* logLevelStrings[3] = {"INFO", "WARN", "ERROR"}; // For printing out log levels

    std::vector<Log> logs;
    const int logLimit = 200; // Maximum amount of logs before vector is cleared

    const int printoutBufSize = 200; // Maximum printout message size
    bool isWritingFile = true;

    std::fstream logFile; // Open stream for writing to log file
    const char* logFilepath = "logger.log";

    void GetLogString(Log log, char* buf, int len);
    void Clear();
};