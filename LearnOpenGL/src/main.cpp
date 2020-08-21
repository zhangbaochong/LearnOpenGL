#include <map>
#include <string>
#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "scenes\BaseScene.hpp"
#include "scenes\1.getting_started\HelloTriangleScene.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::map<std::string, BaseScene*> g_scenes = {
    {"HelloTriangle", new HelloTriangleScene()}
};

BaseScene* getScene(std::string sceneName)
{
    return g_scenes[sceneName];
}

int main() {
    BaseScene* scene = getScene("HelloTriangle");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(scene->getWidth(), scene->getHeight(), "LearnOpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// 初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to init glad" << std::endl;
		return -1;
	}

	scene->onInit();

	while (!glfwWindowShouldClose(window))
	{
		// 输入
		processInput(window);

		scene->onGUI();

		scene->onRender();

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	scene->onRelease();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}