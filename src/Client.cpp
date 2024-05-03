#include "Scripting/python.hpp"
#include <imgui.h>
#include <string>
#include "Client.hpp"

namespace Client
{
    void showHostConfigurationWindow(bool* p_open)
    {
        static char hostname[50];
        static char hostPort[6];
        static char playerName[50];
        static char playerID[50];
        static char numOfPlayers[10];

        static Connection connection;
        static std::string connectionStatus;

        ImGui::Begin("Host Configuration");
        ImGui::InputTextWithHint("Host Name", "Address to the server", hostname, 50);
        ImGui::InputTextWithHint("Host Port", "Port to the server", hostPort, 6);
        ImGui::InputTextWithHint("Player Name", "Name that shows in game", playerName, 50);
        ImGui::InputTextWithHint("Player ID", "Used to identify player between games", playerID, 50);
        ImGui::InputTextWithHint("Number of Players", "The amount of bots to be used", numOfPlayers, 10);
        if (ImGui::Button(connection.IsConnected() ? "Disconnect" : "Connect"))
        {
            if ( connection.IsConnected())
                connection.Disconnect();
            if (!connection.IsConnected())
                connection.Connect(hostname, hostPort, playerName, playerID);
        }
        ImGui::LabelText(connection.IsConnected() ? "Connected" : "Not Connected", "");

        ImGui::End();
    }


    void showGameWindow(bool* p_open)
    {
        ImGui::Begin("Game");
        ImGui::LabelText("Here is a window showing a game instance, I promise :)", "");
        ImGui::End();
    }

    void showScriptSelectWindow(bool* p_open)
    {
        ImGui::Begin("Bot Selector");

        static char scriptPath[50];
        ImGui::InputText("Script Path", scriptPath, 50);

        static std::vector<std::string> languages = {"Python", "C++", "C#"};
        static int languageIdx = 0;

        static Client::PythonEngine pyEngine(L"./client.exe");

        if (ImGui::BeginCombo("Language", languages[languageIdx].c_str()))
        {
            for (int i = 0; i < languages.size(); i++)
            {
                const bool is_selected = (i == languageIdx);
                if (ImGui::Selectable(languages[i].c_str(), is_selected))
                    languageIdx = i;
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Test Bot"))
        {
            if (languages[languageIdx] == "Python")
            {
                PythonEngine::PythonScript myScript(scriptPath);
                pyEngine.RunScript(myScript);
            }
        }

        ImGui::End();
    }
} // namespace Client
