#include "scop.h"
#include "../gl3w/src/gl3w.c"

t_scop *init_struct()
{
	t_scop *scop;
	if (!(scop = (t_scop *)(malloc(sizeof(t_scop)))))
		exit(1);

	scop->pos.x = 0;
	scop->pos.y = 0;
	scop->pos.z = -20;
	scop->rot.x = 0;
	scop->rot.y = 0;
	scop->rot.z = 0;
	scop->faceColors = 0;
	scop->lightStop = 0;
	init_mat4(&scop->model);
	init_mat4(&scop->view);
	mat4x4_perspective(&scop->projection, 45.0, 1920.0f / 1080.0f, 0.1f, 5000.0f);
	return scop;
}

int main(int argc, char *argv[])
{
	t_scop *scop = init_struct();
	t_shader shader = read_path();

	if (argc == 2)
	{
		load_file_obj(argv[1], scop);
	}
	else
	{
		printf("Usage: ./scop [obj]\n");
		return 0;
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "SCOP", NULL, NULL); // Windowed
	glfwMakeContextCurrent(window);
	gl3wInit();
	GLint tex;
	if (!(tex = loadTex("./textures/chat.jpg")))
		exit(1);

	unsigned int shaderProgram = compile_shader_test(shader.vertexShaderSource, shader.fragmentShaderSource);

	glUseProgram(shaderProgram);

	unsigned int VAO, VBO, COLORS, COLORSFACE;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &COLORS);
	glGenBuffers(1, &COLORSFACE);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_face) * scop->face_nb * 3, scop->object, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)offsetof(t_vertex_face, texture));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)offsetof(t_vertex_face, normal));

	glBindBuffer(GL_ARRAY_BUFFER, COLORS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->face_nb * 9), scop->colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, COLORSFACE);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->face_nb * 9), scop->colorsFace, GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		input_key(scop, window);

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUseProgram(shaderProgram);

		t_mat4 transform;
		t_mat4 rotation;
		init_mat4(&transform);
		init_mat4(&rotation);
		rotation = mat4x4_rotx(rotation, scop->rot.x);
		rotation = mat4x4_roty(rotation, scop->rot.y);
		rotation = mat4x4_rotz(rotation, scop->rot.z);
		scop->view = v_add((t_vec3){scop->pos.x, scop->pos.y, scop->pos.z, 1.0f});

		scop->view = mat4x4_mult(scop->view, rotation);
		glUseProgram(shaderProgram);
		GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
		GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &scop->model.mat[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &scop->view.mat[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &scop->projection.mat[0][0]);

		GLuint objectColor = glGetUniformLocation(shaderProgram, "objectColor");
		GLuint lightColor = glGetUniformLocation(shaderProgram, "lightColor");
		GLuint lightPos = glGetUniformLocation(shaderProgram, "lightPos");
		GLuint faceColorPos = glGetUniformLocation(shaderProgram, "faceColors");
		GLuint viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");

		GLfloat objColor[3] = {1.0f, 1.0f, 1.0f};
		GLfloat ligColor[3] = {1.0f, 1.0f, 1.0f};
		GLfloat viewPosSpecular[3] = {scop->pos.x, scop->pos.y, scop->pos.z};
		GLfloat ligPos[3];
		if (scop->lightStop == 0)
		{

			ligPos[0] = sinf(currentFrame) * 1000.0f;
			ligPos[1] = cosf(currentFrame) * 1000.0f;
			ligPos[2] = cosf(currentFrame) * 1000.0f;
		}

		glUniform3fv(objectColor, 1, objColor);
		glUniform3fv(lightColor, 1, ligColor);
		glUniform3fv(lightPos, 1, ligPos);
		glUniform3fv(viewPosLoc, 1, viewPosSpecular);
		glUniform1i(faceColorPos, scop->faceColors);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, scop->face_nb * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &COLORS);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
}