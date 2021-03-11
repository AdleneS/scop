#include "scop.h"

unsigned int compile_shader_test(char *vertexSource, char *fragmentSource)
{
	printf("-> %s \n\n", vertexSource);
    printf("-> %s \n\n", fragmentSource);
    unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const char *const *)&vertexSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const char *const *)&fragmentSource, NULL);
	glCompileShader(fragmentShader);


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