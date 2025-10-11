#include "Application.h"
#include "imgui/imgui.h"
#include "Logger.h"

// === Changes to Starter Code ===
// Simplified Log info and log game event to a single log with levels (may change it back later)
// Removed all ImGui drawing functions from directly within the game render loop (now they are in the logger draw)
// I did not change anything in the given main files


namespace ClassGame {
        //
        // our global variables
        //

        //
        // game starting point
        // this is called by the main render loop in main.cpp
        //

        bool isLogWindowShown = true;

        void GameStartUp() 
        {
            // Initialize logging system
            Logger& logger = Logger::GetInstance();

            logger.AddLog("Logger started successfully", LogLevel::INFO);
            // logger.LogInfo("Game started successfully");
            // logger.LogGameEvent("Application initialized");
        }

        //
        // game render loop
        // this is called by the main render loop in main.cpp
        //
        void RenderGame() 
        {
            ImGui::DockSpaceOverViewport();
            ImGui::ShowDemoWindow();

            ShowLogWindow();

            /* ImGui::Begin("ImGui Log Demo");
            ImGui::LogButtons();

            if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
            {
                ImGui::LogToClipboard();
                ImGui::LogText("Hello, world!");
                ImGui::LogFinish();
            }
            ImGui::End(); */
        }

        //
        // end turn is called by the game code at the end of each turn
        // this is where we check for a winner
        //
        void EndOfTurn() 
        {
        }


        void ShowLogWindow(bool *p_open)
        {
            Logger& logger = Logger::GetInstance();
            logger.Draw(p_open);
        }

        void ToggleLogWindow()
        {
            Logger& logger = Logger::GetInstance();
            IsLogWindowVisible() ? logger.SetEnabled(false) : logger.SetEnabled(true);
        }

        bool IsLogWindowVisible()
        {
            Logger& logger = Logger::GetInstance();
            return logger.GetEnabled();
        }
}
