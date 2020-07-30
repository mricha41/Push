#include "graphics/Mesh.hpp"

using namespace pk;

Mesh::Mesh(GLfloat *vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices)
{
    m_data.d_indexCount = numindices;

	glGenVertexArrays(1, &m_data.d_VAO);
	glBindVertexArray(m_data.d_VAO);

	glGenBuffers(1, &m_data.d_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.d_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numindices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_data.d_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_data.d_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numvertices, vertices, GL_STATIC_DRAW);

    //Position in layout = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)0);
	glEnableVertexAttribArray(0);
	//colors in layout = 1
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);
	//Texture coordinates in layout = 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 7));
	glEnableVertexAttribArray(2);
	//Normal coordinates in layout = 3
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 9));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	updateNormals(vertices, numvertices, indices, 12);
}

Mesh::~Mesh()
{
	clear();
}

void Mesh::updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int * indices, unsigned int stride)
{
    for (size_t i = 0; i < m_data.d_indexCount; i += 3)
	{
		unsigned int in0 = indices[i] * stride;
		unsigned int in1 = indices[i + 1] * stride;
		unsigned int in2 = indices[i + 2] * stride;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += 9; in1 += 9; in2 += 9;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / stride; i++)
	{
		unsigned int nOffset = i * stride + 9;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void Mesh::draw(GLStates& states)
{
    m_data.d_glStates = states;

    m_data.d_model = glm::mat4(1.0f);
    glm::mat4 scale = glm::scale(m_data.d_model, glm::vec3(m_data.d_scale, 1.0f));
    glm::mat4 rot = glm::rotate(m_data.d_model, glm::radians(m_data.d_angle), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 tran = glm::translate(glm::mat4(1.0f), glm::vec3(m_data.d_position, 0.0f));
    m_data.d_model = tran * rot * scale * m_data.d_model;
    m_data.d_model = glm::translate(m_data.d_model, glm::vec3(-getOrigin(), 0.f));
    glUniformMatrix4fv(*m_data.d_glStates.modelLocation, 1, GL_FALSE, glm::value_ptr(m_data.d_model));

	glBindVertexArray(m_data.d_VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.d_IBO);

	glDrawElements(GL_TRIANGLES, m_data.d_indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
