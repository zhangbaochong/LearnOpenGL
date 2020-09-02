#include "Dashboard.h"

std::string Dashboard::s_sceneName = "LearnOpenGL Scene";
bool Dashboard::s_enabledCursor = false;

void Dashboard::initSceneName(std::string sceneName)
{
    Dashboard::s_sceneName = sceneName;
}

void Dashboard::setEnabledCursor(bool status)
{
	Dashboard::s_enabledCursor = status;
}

void Dashboard::draw(float fps)
{
	ImGui::SetNextWindowPos(ImVec2(10,10));
	ImGui::SetNextWindowBgAlpha(0.35f);					// 背景透明 35% 的alpha值
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDecoration |					// 不需要标题、不需要调整大小、不需要滚动条、不需要折叠
		ImGuiWindowFlags_AlwaysAutoResize |				// 自动调整大小
		ImGuiWindowFlags_NoSavedSettings |				// 不需要保存会加载布局信息
		ImGuiWindowFlags_NoFocusOnAppearing |			// 显示时不需要获取交点
		ImGuiWindowFlags_NoNav;
	bool isOpen;
	ImGui::Begin("Dashboard", &isOpen, window_flags);
	ImGui::Text(
		"SceneName : %s\n", Dashboard::s_sceneName.c_str());
	ImGui::Separator();
	ImGui::Text("FPS : %.1f", fps);
	ImGui::Separator();
	std::string enabledCursorStr;
	if (Dashboard::s_enabledCursor)
	{
		enabledCursorStr = "true";
	}
	else
	{
		enabledCursorStr = "false";
	}
	ImGui::Text("Enabled Cursor(Y): %s", enabledCursorStr.c_str());
	ImGui::End();
}

