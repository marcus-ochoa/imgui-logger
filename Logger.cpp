
#include "Logger.h"
#include "imgui/imgui.h"
#include <vector>
#include <fstream>

// Get singleton instance of logger class
Logger& Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::Draw(bool *p_open)
{
    if (!isEnabled)
    {
        return;
    }

    ImGui::Begin("Logger", p_open);

    // Options popup window
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Write to file", &isWritingFile);
        ImGui::EndPopup();
    }

    // Buttons
    if (ImGui::Button("Options"))
    {
        ImGui::OpenPopup("Options");
    }

    ImGui::SameLine();
    if (ImGui::Button("Test Info"))
    {
        AddLog("This is a test info message", LogLevel::INFO);
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Test Warn"))
    {
        AddLog("Hello this is a test warning message", LogLevel::WARN);
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Test Error"))
    {
        AddLog("Hello this is a test error message", LogLevel::ERROR);
    }

    ImGui::SameLine();
    if (ImGui::Button("Clear"))
    {
        Clear();
    }

    // Printout for logs
    ImGui::BeginChild("Printout");
    for (Log log : logs) {

        char printout[printoutBufSize];
        GetLogString(log, printout, printoutBufSize);

        // Change color of line depending on log level
        ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        switch (log.level)
        {
            case LogLevel::INFO :
                color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case LogLevel::WARN :
                color = ImVec4(1.0f, 0.8f, 0.0f, 1.0f);
                break;
            case LogLevel::ERROR :
                color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
                break;
        }

        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(printout);
        ImGui::PopStyleColor();
    }
    ImGui::EndChild();

    ImGui::End();
}

void Logger::AddLog(const char* message, LogLevel level)
{
    Log newLog = Log(message, level, ImGui::GetTime());

    if (isWritingFile)
    {
        if (!logFile.is_open())
        {
            logFile.open(logFilepath, std::fstream::out);
        }

        char printout[printoutBufSize];
        GetLogString(newLog, printout, printoutBufSize);

        logFile << printout << std::endl;
    }

    if ((int) logs.size() >= logLimit)
    {
        Clear();
    }
    logs.push_back(newLog);
}

void Logger::GetLogString(Log log, char* buf, int len)
{
    snprintf(buf, len, "[%f] [%s] %s", log.time, logLevelStrings[log.level], log.message);
}

void Logger::Clear()
{
    logs.clear();
}

void Logger::SetEnabled(bool enabledState)
{
    isEnabled = enabledState;
}