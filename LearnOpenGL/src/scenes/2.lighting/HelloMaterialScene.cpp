#include "HelloMaterialScene.h"

HelloMaterialScene::HelloMaterialScene() :
	m_VAO(0),
	m_VBO(0)
{
	m_model = glm::mat4(1.f);
	m_view = glm::mat4(1.f);
	m_projection = glm::mat4(1.f);
	m_model = glm::scale(m_model, glm::vec3(5, 2, 5));
	m_view = MainCamera::getInstance()->getViewMatrix();
	m_projection = MainCamera::getInstance()->getProjMatrix();
	m_light = std::make_shared<Light>();
}

HelloMaterialScene::~HelloMaterialScene() {}

void HelloMaterialScene::onInit()
{
	m_shader = std::make_shared<Shader>("shaders/2.lighting/HelloMaterial.vert",
		"shaders/2.lighting/HelloMaterial.frag");

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_shader->use();
	m_light->init();
	// ¿ªÆôÉî¶È²âÊÔ
	glEnable(GL_DEPTH_TEST);
}

void HelloMaterialScene::onRender()
{
	// äÖÈ¾Ö¸Áî
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	MainCamera::getInstance()->updateCameraVectors();
	// äÖÈ¾Èý½ÇÐÎ
	m_shader->use();
	// ÉèÖÃ±ä»»¾ØÕó
	m_view = MainCamera::getInstance()->getViewMatrix();
	m_projection = MainCamera::getInstance()->getProjMatrix();

	m_shader->setMat4("model", m_model);
	m_shader->setMat4("view", m_view);
	m_shader->setMat4("projection", m_projection);

	m_shader->setVec3("lightPos", m_light->getPosition());
	m_shader->setVec3("viewPos", MainCamera::getInstance()->m_position);
	m_shader->setVec3("lightColor", m_light->m_lightColor[0], m_light->m_lightColor[1], m_light->m_lightColor[2]);

	m_shader->setFloat("ambientStrength", m_ambientStrength);
	m_shader->setVec3("material.ambient", m_ambient[0], m_ambient[1], m_ambient[2]);
	m_shader->setVec3("material.diffuse", m_diffuse[0], m_diffuse[1], m_diffuse[2]);
	m_shader->setVec3("material.specular", m_specular[0], m_specular[1], m_specular[2]);
	m_shader->setFloat("material.specularGloss", m_specularGloss);

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	m_light->draw();
}


void HelloMaterialScene::onGUI()
{
	ImGui::SetNextWindowBgAlpha(0.35f);
	ImGui::Begin("Light Panel");
	ImGui::DragFloat("ambientStrength", &m_ambientStrength, 0.1f, 0, 1.f);
	ImGui::BulletText("Cube Material");
	ImGui::DragFloat3("ambient", m_ambient, 0.1f, 0, 1.f);
	ImGui::DragFloat3("diffuse", m_diffuse, 0.1f, 0, 1.f);
	ImGui::DragFloat3("specular", m_specular, 0.1f, 0, 1.f);
	ImGui::DragFloat("specularGloss", &m_specularGloss, 1, 0, 256);
	ImGui::End();
}

void HelloMaterialScene::onRelease()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}
