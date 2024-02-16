#include "LightCaster.h"

LightCaster::LightCaster()
{
}

LightCaster::~LightCaster()
{
}

void LightCaster::LoadShader(std::string vertex, std::string fragment)
{
	m_shader = new Shader(vertex.c_str(), fragment.c_str());
}

void LightCaster::GenerateBuffers()
{
}

void LightCaster::Render(glm::vec3 vpos, glm::mat4 view)
{
}

void LightCaster::Unbind()
{
}

void LightCaster::setVBO(unsigned int vbo)
{
	VBO = vbo;
}
