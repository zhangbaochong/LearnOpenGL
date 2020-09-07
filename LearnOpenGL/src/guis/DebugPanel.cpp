#include "DebugPanel.h"
#include "utils/MainCamera.h"

std::vector<std::string> DebugPanel::s_logs;
float DebugPanel::s_background[4] = {
    MainCamera::getInstance()->m_backgroudColor.x, MainCamera::getInstance()->m_backgroudColor.y, MainCamera::getInstance()->m_backgroudColor.z,
    MainCamera::getInstance()->m_backgroudColor.w
};

void DebugPanel::draw()
{
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("Debug Panel");
    if (ImGui::CollapsingHeader("Shortcuts"))
    {
        ImGui::Text("Exiting Application(Esc)");
    }

    if (ImGui::CollapsingHeader("Camera"))
    {
        ImGui::ColorEdit4("Background", s_background);
        MainCamera::getInstance()->m_backgroudColor = glm::vec4(s_background[0], s_background[1], s_background[2], s_background[3]);
    }

    if (ImGui::CollapsingHeader("Logs"))
    {
        for (auto log : s_logs)
        {
            ImGui::Text(log.c_str());
        }
    }
    ImGui::End();
}

void DebugPanel::LogError(std::string content)
{
    s_logs.push_back("[ERROR] : " + content);
}

void DebugPanel::LogInfo(std::string content)
{
    s_logs.push_back("[INFO] : " + content);
}

void DebugPanel::LogWarn(std::string content)
{
    s_logs.push_back("[WARNING] : " + content);
}

