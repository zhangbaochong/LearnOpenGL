#include "HelloTriangleScene.h"

HelloTriangleScene::HelloTriangleScene()
{
}

HelloTriangleScene::~HelloTriangleScene(){}

void HelloTriangleScene::onInit()
{
    m_shader = std::make_shared<Shader>("shaders/1.getting_started/HelloTriangle.vert", 
	"shaders/1.getting_started/HelloTriangle.frag");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void HelloTriangleScene::onRender()
{
	// äÖÈ¾Ö¸Áî
	glClearColor(0.1f, 0.2f, 0.3f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT);

	// äÖÈ¾Èý½ÇÐÎ
	m_shader->use();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


void HelloTriangleScene::onGUI()
{
	bool test;
	ImGui::Begin("Another Window", &test);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::Text("Hello from another window!");
	ImGui::End();
}

void HelloTriangleScene::onRelease()
{
}
