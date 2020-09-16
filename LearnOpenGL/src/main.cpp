#include <map>
#include <string>
#include "CommonHeader.h"
#include "utils/Timer.h"
#include "scenes/BaseScene.h"
#include "scenes/1.getting_started/HelloTriangleScene.h"
#include "scenes/1.getting_started/HelloTextureScene.h"
#include "scenes/1.getting_started/HelloCoordinateSystemScene.h"
#include "scenes/1.getting_started/HelloCameraScene.h"
#include "scenes/2.lighting/HelloLightScene.h"
#include "scenes/2.lighting/HelloMaterialScene.h"

void initImgui(GLFWwindow* window);
void imguiNewFrame();
void releaseImgui();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void onMouseMove(GLFWwindow* window, double xpos, double ypos);
void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

std::map<std::string, BaseScene*> g_scenes = {
    {"HelloTriangle", new HelloTriangleScene()},
	{"HelloTexture", new HelloTextureScene()},
	{"HelloCoordinateSystem", new HelloCoordinateSystemScene()},
	{"HelloCamera", new HelloCameraScene()},
	{"HelloLight", new HelloLightScene()},
	{"HelloMaterial", new HelloMaterialScene()}
};

BaseScene* getScene(std::string sceneName)
{
    return g_scenes[sceneName];
}


int main() {
	//std::string sceneName = "HelloTriangle";
	//std::string sceneName = "HelloTexture";
	//std::string sceneName = "HelloCoordinateSystem";
	//std::string sceneName = "HelloCamera";
	//std::string sceneName = "HelloLight";
	std::string sceneName = "HelloMaterial";

    BaseScene* scene = getScene(sceneName);
	Dashboard::initSceneName(sceneName);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scene->getWidth(), scene->getHeight(), "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetScrollCallback(window, onMouseScroll);
	glfwSetKeyCallback(window, onKeyEvent);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// 初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init glad" << std::endl;
		return -1;
	}

	scene->onInit();
	glfwSetWindowUserPointer(window, scene);
	initImgui(window);
	
	int frameCount = 0;

	float lastTime = glfwGetTime();
	float lastTimeForFPS = lastTime;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		// 计算deltaTime
		float currentTime = glfwGetTime();
		Timer::deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		// 计算fps
		++frameCount;
		if (currentTime - lastTimeForFPS > 1.f)
		{
			Timer::FPS = frameCount;
			frameCount = 0;
			lastTimeForFPS = currentTime;
		}

		imguiNewFrame();
		// 输入
		processInput(window);

		glClearColor(MainCamera::getInstance()->m_backgroudColor[0], MainCamera::getInstance()->m_backgroudColor[1], 
			MainCamera::getInstance()->m_backgroudColor[2], MainCamera::getInstance()->m_backgroudColor[3]);
		
		scene->onRender();

		scene->onGUI();

		Dashboard::draw(Timer::FPS);
		DebugPanel::draw();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
	}
	releaseImgui();
	glfwTerminate();
	scene->onRelease();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void initImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.WantCaptureMouse = true;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
}

void imguiNewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void releaseImgui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void onMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	if (Dashboard::s_enabledCursor)
		return;
	auto painter = static_cast<BaseScene*>(glfwGetWindowUserPointer(window));
	if (painter != nullptr)
		painter->onMouseMoveCallback(window, xpos, ypos);
}

void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (Dashboard::s_enabledCursor)
	{
		return;
	}
	auto painter = static_cast<BaseScene*>(glfwGetWindowUserPointer(window));
	if (painter != nullptr)
		painter->onMouseScrollCallBack(window, xoffset, yoffset);
}

void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		Dashboard::s_enabledCursor = !Dashboard::s_enabledCursor;
		if (Dashboard::s_enabledCursor)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (Dashboard::s_enabledCursor)
	{
		return;
	}

	auto painter = static_cast<BaseScene*>(glfwGetWindowUserPointer(window));
	if (painter != nullptr)
		painter->handleInput(window);
}
