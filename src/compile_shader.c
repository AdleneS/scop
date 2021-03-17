#include "scop.h"

void shader_error_handler(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("%s\nERROR::SHADER::%d::COMPILATION_FAILED\n", infoLog, shader);
	}
}

unsigned int compile_shader_test(char *vertexSource, char *fragmentSource)
{
	unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char *const *)&vertexSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char *const *)&fragmentSource, NULL);
	glCompileShader(fragmentShader);
	shader_error_handler(vertexShader);
	shader_error_handler(fragmentShader);
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}
