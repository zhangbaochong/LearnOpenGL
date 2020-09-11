#include "DebugPanel.h"
#include "utils/MainCamera.h"

std::vector<std::string> DebugPanel::s_logs;
float DebugPanel::s_position[3] = { MainCamera::getInstance()->m_position.x, 
MainCamera::getInstance()->m_position.y, 
MainCamera::getInstance()->m_position.z };

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
        ImGui::ColorEdit4("Background", MainCamera::getInstance()->m_backgroudColor);
        ImGui::Separator();
        ImGui::DragFloat3("Postition", s_position, 1.f, -100.f, 100.f, "%.1f");
        //MainCamera::getInstance()->m_position = { s_position[0], s_position[1], s_position[2] };
        ImGui::Separator();
        ImGui::DragFloat("Field of View", &MainCamera::getInstance()->m_FOV);
        ImGui::DragFloat("Near", &MainCamera::getInstance()->m_near);
        ImGui::DragFloat("Far", &MainCamera::getInstance()->m_far);
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

