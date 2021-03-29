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
	//print_array(scop->colors, scop->face_nb * 9);
	//print_vertex_face(scop->object, scop->face_nb * 3);
	//print_vertex_face(scop->object, );
	//print_array_face(scop->faces, scop->face_nb * 3);
	//print_array(scop->vertices, scop->size * 6);
	//print_array_vn(scop->normal, scop->normal_nb * 3);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "SCOP", NULL, NULL); // Windowed
	glfwMakeContextCurrent(window);
	gl3wInit();
	GLint tex = loadTex("./textures/marble.jpg");

	//Init Shaders and compile it
	unsigned int shaderProgram = compile_shader_test(shader.vertexShaderSource, shader.fragmentShaderSource);
	//unsigned int shaderProgramLight = compile_shader_test(shader.vertexShaderLight, shader.fragmentShaderLight);

	glUseProgram(shaderProgram);

	unsigned int VAO, VBO, COLORS;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &COLORS);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vertex_face) * scop->face_nb * 3, scop->object, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)offsetof(t_vertex_face, texture));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex_face), (void *)offsetof(t_vertex_face, normal));

	printf("\n%d | %d \n", scop->vertex_nb, scop->face_nb);
	// 3. then set our vertex attributes pointers

	// Activate the model's color Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, COLORS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->face_nb * 9), scop->colors, GL_STATIC_DRAW);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	// Activate the model's color Buffer Object
	// Bind the color Buffer Object to the 'a_Color' shader variable

	//unsigned int lightVAO;
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);
	//// we only need to bind to the VBO, the container's VBO's data already contains the data.
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//// set the vertex attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	//glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Polygon Mode wireframe
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
		GLfloat ligPos[3] = {sinf(currentFrame) * 100.0f, cosf(currentFrame) * 100.0f, cosf(currentFrame) * 100.0f};
		glUniform3fv(objectColor, 1, objColor);
		glUniform3fv(lightColor, 1, ligColor);
		glUniform3fv(lightPos, 1, ligPos);
		glUniform3fv(viewPosLoc, 1, viewPosSpecular);
		glUniform1i(faceColorPos, scop->faceColors);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, scop->face_nb * 3);

		//glUseProgram(shaderProgramLight);
		// t_mat4 lModel;

		// init_mat4(&lModel);
		// viewLoc = glGetUniformLocation(shaderProgramLight, "view");
		// projectionLoc = glGetUniformLocation(shaderProgramLight, "projection");
		// lModel = v_add((t_vec3){ligPos[0], ligPos[1], ligPos[2], 1.0f});
		//glDrawElements(GL_TRIANGLES, scop->face_nb * 3, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, scop->face_nb * 3);

		// modelLoc = glGetUniformLocation(shaderProgramLight, "model");
		// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &lModel.mat[0][0]);
		// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &scop->view.mat[0][0]);
		// glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &scop->projection.mat[0][0]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &COLORS);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
}