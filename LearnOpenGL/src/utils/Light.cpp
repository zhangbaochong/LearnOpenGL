#include "Light.h"
#include "utils/MainCamera.h"

Light::Light(glm::vec3 position):
	m_VAO(0),
	m_VBO(0)
{
	m_position = position;
	m_model = glm::mat4(1.f);
	m_view = glm::mat4(1.f);
	m_projection = glm::mat4(1.f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::scale(m_model, glm::vec3(0.1f, 0.1f, 0.1f));
}

Light::~Light()
{}

void Light::init()
{
	m_shader = std::make_shared<Shader>("shaders/utils/Light.vert",
		"shaders/utils/Light.frag");
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	m_shader->use();
	// 开启深度测试
	glEnable(GL_DEPTH_TEST);
}

void Light::draw()
{
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