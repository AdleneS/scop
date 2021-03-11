#include "scop.h"

unsigned int compile_shader_element(char *shader)
{
    unsigned int shaderElement = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderElement, 1, (const char *const *)&shader, NULL);
    glCompileShader(shaderElement);
    return shaderElement;
}

unsigned int compile_shader_test()
{
    t_shader *shader = read_path();
    unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//Attach shaders
    while (shader->next)
    {
        unsigned int shaderElement = compile_shader_element(shader->shader);
        glAttachShader(shaderProgram, shaderElement);
        glLinkProgram(shaderProgram);
        glDeleteShader(shaderElement);
        shader = shader->next;
    }

	return shaderProgram;
}