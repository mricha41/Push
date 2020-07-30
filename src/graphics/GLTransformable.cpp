#include "graphics/GLTransformable.hpp"

#include <glm/gtc/type_ptr.hpp>

using namespace pk;

GLTransformable::GLTransformable()
{
    m_data.d_VAO = 0;
    m_data.d_VBO = 0;
    m_data.d_IBO = 0;
    m_data.d_indexCount = 0;
    m_data.d_model = glm::mat4(1.0f);
    m_data.d_glStates = {0, 0, 0};
    m_data.d_origin = glm::vec2(0.f, 0.f);
    m_data.d_position = glm::vec2(0.f, 0.f);
    m_data.d_angle = 0.f;
    m_data.d_scale = glm::vec2(1.f, 1.f);
    m_data.d_rect = GLRect({0.f, 0.f, 0.f, 0.f});
}

void GLTransformable::clear()
{
    if (m_data.d_IBO != 0)
	{
		glDeleteBuffers(1, &m_data.d_IBO);
		m_data.d_IBO = 0;
	}

    if (m_data.d_VBO != 0)
	{
		glDeleteBuffers(1, &m_data.d_VBO);
		m_data.d_VBO = 0;
	}

	if (m_data.d_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_data.d_VAO);
		m_data.d_VAO = 0;
	}

	m_data.d_indexCount = 0;
}

GLTransformable::~GLTransformable()
{
    clear();
}
