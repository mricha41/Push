#include "graphics/GLSprite.hpp"

#include "graphics/GLTexture.hpp"

using namespace pk;

GLSprite::GLSprite()
:
    m_texture(new GLTexture("images/white_square.png")),
    m_vertexColors {
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f
    },
    m_textureRect({0.f,0.f,64.f,64.f})
{
    m_fillColor = glm::vec4(1.f, 1.f, 1.f, 1.f);

	setRect({0.f, 0.f, 64.f, 64.f});
	setPosition({0.f, 0.f});
	setOrigin({0.f, 0.f});
	setWidth(0.f);
	setHeight(0.f);

	updateGeometry();
}

GLSprite::GLSprite(GLTexture& t, GLRect rect)
:
    m_texture(&t),
    m_vertexColors {
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f
    }
{
    m_fillColor = glm::vec4(1.f, 1.f, 1.f, 1.f);

    setRect({0.f, 0.f, rect.d_width, rect.d_height});
	setPosition({0.f, 0.f});
	setOrigin({rect.d_width/2.f, rect.d_height/2.f});
	setWidth(rect.d_width);
	setHeight(rect.d_height);

	m_textureRect = rect;

	updateGeometry();
}

GLSprite::~GLSprite()
{

}

void GLSprite::setFillColor(glm::vec4 fillColor)
{
    m_fillColor = fillColor;

    for(int i=0; i<16; i+=4)
    {
        m_vertexColors[i] = fillColor.r;
        m_vertexColors[i+1] = fillColor.g;
        m_vertexColors[i+2] = fillColor.b;
        m_vertexColors[i+3] = fillColor.a;
    }

    updateGeometry();
}

void GLSprite::setVertexColors(GLfloat colors [16])
{
    for(int i=0; i<16; ++i)
        m_vertexColors[i] = colors[i];

    updateGeometry();
}

void GLSprite::updateNormals(GLfloat * vertices, unsigned int verticeCount, unsigned int stride)
{
    GLfloat indices[] = {
        0,1,2,3,4,5
    };

    for (size_t i = 0; i < 6; i += 3)
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

void GLSprite::updateGeometry()
{
    unsigned int indices[] = {
        0, 1, 2,
		2, 3, 0
    };

    m_data.d_indexCount = sizeof(indices)/sizeof(indices[0]);

    //calculate the offsets based on
    //the size of the texture, the rect corresponding
    //to the frame size of the sprite (bounding rect)
    //and the position given in the texture
    //u/v coordinates are normalized, which is accomplished
    //here rather than forcing the user to use normalized
    //coords they can just pass in pixel coords
    GLRect r = m_texture->getTextureRect(); //given in pixel coords
    GLRect offset; //normalized
    offset.d_left = m_textureRect.d_left/r.d_width;
    offset.d_top = m_textureRect.d_top/r.d_height;
    offset.d_width = m_textureRect.d_width/r.d_width;
    offset.d_height = m_textureRect.d_height/r.d_height;

    GLfloat vertices[] = {
        // position                             colors                                                                      texture     normals
	    //x         y                 z	    r                   g                   b                   a                   u	  v		nx	  ny    nz
		0.f,        0.0f,           0.0f,   m_vertexColors[0], m_vertexColors[1], m_vertexColors[2], m_vertexColors[3],     offset.d_left, offset.d_top, 0.0f, 0.0f, 0.0f,//top left
		getWidth(), 0.0f,           0.0f,   m_vertexColors[4], m_vertexColors[5], m_vertexColors[6], m_vertexColors[7],     offset.d_left + offset.d_width, offset.d_top, 0.0f, 0.0f, 0.0f,//top right
		getWidth(), getHeight(),    0.0f,   m_vertexColors[8], m_vertexColors[9], m_vertexColors[10], m_vertexColors[11],   offset.d_left + offset.d_width, offset.d_top + offset.d_height, 0.0f, 0.0f, 0.0f,//bottom left
		0.f,        getHeight(),    0.0f,   m_vertexColors[12], m_vertexColors[13], m_vertexColors[14], m_vertexColors[15], offset.d_left, offset.d_top + offset.d_height, 0.0f, 0.0f, 0.0f//bottom right
	};

    glGenVertexArrays(1, &m_data.d_VAO);
	glBindVertexArray(m_data.d_VAO);

	glGenBuffers(1, &m_data.d_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.d_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * m_data.d_indexCount, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_data.d_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_data.d_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * 48, vertices, GL_STATIC_DRAW);

    //positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, 0);
	glEnableVertexAttribArray(0);

	//colors
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    //Texture coordinates in layout = 2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 7));
	glEnableVertexAttribArray(2);

	//Normal coordinates in layout = 3
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 12, (void*)(sizeof(vertices[0]) * 9));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	updateNormals(vertices, 48, 12);
}

void GLSprite::draw(GLStates& states)
{
    m_texture->use();

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

	m_texture->disable();
}
