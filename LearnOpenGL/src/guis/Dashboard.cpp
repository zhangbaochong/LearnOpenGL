#include "Dashboard.h"

std::string Dashboard::s_sceneName = "LearnOpenGL Scene";

void Dashboard::initSceneName(std::string sceneName)
{
    Dashboard::s_sceneName = sceneName;
}

void Dashboard::draw(float fps)
{
	ImGui::SetNextWindowPos(ImVec2(10,10));
	ImGui::SetNextWindowBgAlpha(0.35f);					// ����͸�� 35% ��alphaֵ
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDecoration |					// ����Ҫ���⡢����Ҫ������С������Ҫ������������Ҫ�۵�
		ImGuiWindowFlags_AlwaysAutoResize |				// �Զ�������С
		ImGuiWindowFlags_NoSavedSettings |				// ����Ҫ�������ز�����Ϣ
		ImGuiWindowFlags_NoFocusOnAppearing |			// ��ʾʱ����Ҫ��ȡ����
		ImGuiWindowFlags_NoNav;
	bool isOpen;
	ImGui::Begin("Dashboard", &isOpen, window_flags);
	ImGui::Text(
		"SceneName : %s\n", Dashboard::s_sceneName.c_str());
	ImGui::Separator();
	ImGui::Text("FPS : %.1f", fps);
	ImGui::End();
}