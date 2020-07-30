#include "graphics/Shader.hpp"

using namespace pk;

Shader::Shader()
:
    m_shaderID(),
	m_uniformModel(),
	m_uniformProjection()
{

}

Shader::Shader(const char* vertexLocation, const char* fragmentLocation)
:
    m_shaderID(),
	m_uniformModel(),
	m_uniformProjection()
{
    load(vertexLocation, fragmentLocation);
}

Shader::~Shader()
{
	clear();
}

void Shader::clear()
{
	if (m_shaderID != 0)
	{
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	m_uniformModel = 0;
	m_uniformProjection = 0;
	m_uniformView = 0;
}

void Shader::loadFromString(const char* vertexCode, const char* fragmentCode)
{
	compile(vertexCode, fragmentCode);
}

void Shader::load(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexString = read(vertexLocation);
	std::string fragmentString = read(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compile(vertexCode, fragmentCode);
}

std::string Shader::read(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::use()
{
	glUseProgram(m_shaderID);
}

void Shader::attach(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::compile(const char* vertexCode, const char* fragmentCode)
{
    m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	attach(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	attach(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	m_uniformProjection = glGetUniformLocation(m_shaderID, "projection");
	m_uniformModel = glGetUniformLocation(m_shaderID, "model");
	m_uniformView = glGetUniformLocation(m_shaderID, "view");
	m_uniformAmbientIntensity = glGetUniformLocation(m_shaderID, "dirLight.d_ambientIntensity");
	m_uniformAmbientColor = glGetUniformLocation(m_shaderID, "dirLight.d_color");
	m_uniformDiffuseIntensity = glGetUniformLocation(m_shaderID, "dirLight.d_diffuseIntensity");
	m_uniformDirection = glGetUniformLocation(m_shaderID, "dirLight.d_direction");
	m_uniformEyePosition = glGetUniformLocation(m_shaderID, "eyePosition");
	m_uniformSpecularIntensity = glGetUniformLocation(m_shaderID, "material.d_specularIntensity");
	m_uniformShininess = glGetUniformLocation(m_shaderID, "material.d_shininess");
}
