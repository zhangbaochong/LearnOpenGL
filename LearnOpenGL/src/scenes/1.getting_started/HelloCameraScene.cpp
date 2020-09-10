#include "HelloCameraScene.h"

HelloCameraScene::HelloCameraScene() :
	m_VAO(0), 
	m_VBO(0)
{
	m_model = glm::mat4(1.f);
	m_view = glm::mat4(1.f);
	m_projection = glm::mat4(1.f);
	m_model = glm::rotate(m_model, 1.f, glm::vec3(0.5f, 1.0f, 0.0f));
	m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
	m_projection = glm::perspective(glm::radians(45.0f), float(this->m_screenWidth) / float(this->m_screenHeight), 0.1f, 100.0f);
}

HelloCameraScene::~HelloCameraScene() {}

void HelloCameraScene::onInit()
{
	m_shader = std::make_shared<Shader>("shaders/1.getting_started/HelloCoordinateSystem.vert",
		"shaders/1.getting_started/HelloCoordinateSystem.frag");

	// 生成纹理
	glGenTextures(1, &m_texture1);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	// 设置环绕过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../resources/textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "ERROR: failed to load image." << std::endl;
	}

	glGenTextures(1, &m_texture2);
	glBindTexture(GL_TEXTURE_2D, m_texture2);
	// 设置环绕过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("../resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "ERROR: failed to load image." << std::endl;
	}


	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_shader->use();
	m_shader->setInt("texture1", 0);
	m_shader->setInt("texture2", 1);

	// 开启深度测试
	glEnable(GL_DEPTH_TEST);

	DebugPanel::LogInfo("Test log.");
}

void HelloCameraScene::onRender()
{
	// 渲染指令
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);

	// 渲染三角形
	m_shader->use();
	// 设置变换矩阵
	m_view = MainCamera::getInstance()->getViewMatrix();
	m_projection = MainCamera::getInstance()->getProjMatrix();

	m_shader->setMat4("model", m_model);
	m_shader->setMat4("view", m_view);
	m_shader->setMat4("projection", m_projection);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


void HelloCameraScene::onGUI()
{
}

void HelloCameraScene::onRelease()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
