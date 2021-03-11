/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaba <asaba@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:48:56 by slopez            #+#    #+#             */
/*   Updated: 2021/03/11 12:31:35 by asaba            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include "../gl3w/src/gl3w.c"

t_scop *init_struct()
{
	t_scop *scop;
	if (!(scop = (t_scop *)(malloc(sizeof(t_scop)))))
		exit(1);

	scop->pos.x = 0;
	scop->pos.y = 0;
	scop->pos.z = 0;
	scop->rot.x = 0;
	scop->rot.y = 0;
	scop->rot.z = 0;
	init_mat4(&scop->model);
	init_mat4(&scop->view);
	mat4x4_perspective(&scop->projection, 45.0, 1920.0f / 1080.0f, 0.1f, 5000.0f);
	return scop;
}

unsigned int compile_shader()
{
	const char *vertexShaderSource = "#version 330 core\n"
									 "layout (location = 0) in vec3 aPos;\n"
									 "layout (location = 1) in vec3 aColor;\n"
									 "layout (location = 2) in vec3 aNormal;\n"
									 "out vec3 ourColor;\n"
									 "out vec3 FragPos;\n"
									 "out vec3 Normal;\n"
									 "uniform mat4 model;\n"
									 "uniform mat4 view;\n"
									 "uniform mat4 projection;\n"
									 "uniform mat4 transform;\n"
									 "void main()\n"
									 "{\n"
									 "FragPos = vec3(model * vec4(aPos, 1.0));\n"
									 "Normal = aNormal;\n"
									 "gl_Position =  projection * view *  vec4(FragPos, 1.0);\n"
									 "ourColor = aColor;\n"
									 "}\0";

	const char *fragmentShaderSource = "#version 330 core\n"
									   "out vec4 FragColor;\n"
									   "in vec3 Normal;\n"
									   "in vec3 FragPos;\n"
									   "in vec3 ourColor;\n"
									   "uniform vec3 lightPos;\n"
									   "uniform vec3 lightColor;\n"
									   "uniform vec3 objectColor;\n"
									   "void main()\n"
									   "{\n"
									   "float ambientStrength = 0.1;\n"
									   "vec3 ambient = ambientStrength * lightColor;\n"
									   "vec3 norm = normalize(Normal);\n"
									   "vec3 lightDir = normalize(lightPos - FragPos);\n"
									   "float diff = max(dot(norm, lightDir), 0.0);\n"
									   "vec3 diffuse = diff * lightColor;\n"
									   "vec3 result = (ambient + diffuse) * objectColor;\n"
									   "FragColor = vec4(result, 1.0);\n\0";

	unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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

unsigned int compile_shader_2()
{

	const char *VertexShaderLight = "#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"uniform mat4 model;\n"
									"uniform mat4 view;\n"
									"uniform mat4 projection;\n"
									"void main()\n"
									"{\n"
									"gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
									"};\n\0";

	const char *fragmentShaderLight = "#version 330 core\n"
									  "out vec4 FragColor;\n"
									  "void main()\n"
									  "{\n"
									  "FragColor = vec4(1.0);\n" // set alle 4 vector values to 1.0
									  "}\n\0";

	unsigned int vertexShader;
	unsigned int fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderLight, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderLight, NULL);
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

int main(int argc, char *argv[])
{
	t_scop *scop = init_struct();

	if (argc == 2)
	{
		load_file_obj(argv[1], scop);
	}
	//print_list(v);
	//print_array_face(scop->faces, scop->face_nb * 3);
	//print_array(scop->vertices, scop->size * 6);
	//print_array_vn(scop->normal, scop->normal_nb);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(1920, 1080, "SCOP", NULL, NULL); // Windowed
	glfwMakeContextCurrent(window);
	gl3wInit();

	//Init Shaders and compile it
	unsigned int shaderProgram;
	shaderProgram = compile_shader();
	unsigned int shaderProgramLight;
	shaderProgramLight = compile_shader_2();

	glUseProgram(shaderProgram);

	unsigned int VAO, VBO, EBO, Colors, normal;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &Colors);
	glGenBuffers(1, &normal);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->size * 3), scop->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	//print_array(vertices, 36 * 5);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (scop->face_nb * 6), scop->faces_v, GL_STATIC_DRAW);

	printf("\n%d | %d \n", scop->size, scop->face_nb);
	// 3. then set our vertex attributes pointers

	// Activate the model's color Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, Colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->face_nb * 3), scop->colors, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (scop->face_nb * 3), scop->normal, GL_STATIC_DRAW);
	// Activate the model's color Buffer Object
	// Bind the color Buffer Object to the 'a_Color' shader variable
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// we only need to bind to the VBO, the container's VBO's data already contains the data.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// set the vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Polygon Mode wireframe
	glDepthFunc(GL_LESS);
	while (!glfwWindowShouldClose(window))
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			scop->rot.x += 0.05;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			scop->rot.x -= 0.05;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			scop->rot.y += 0.05;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			scop->rot.y -= 0.05;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			scop->rot.z += 0.05;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			scop->rot.z -= 0.05;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			scop->pos.x += 0.5;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			scop->pos.x -= 0.5;
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			scop->pos.z += 0.5;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			scop->pos.z -= 0.5;

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);

		t_mat4 transform;
		t_mat4 rotation;
		init_mat4(&transform);
		init_mat4(&rotation);
		rotation = mat4x4_rotx(rotation, scop->rot.x);
		rotation = mat4x4_roty(rotation, scop->rot.y);
		rotation = mat4x4_rotz(rotation, scop->rot.z);
		scop->model = v_add((t_vec3){scop->pos.x, scop->pos.y, scop->pos.z, 1.0f});

		scop->model = mat4x4_mult(scop->model, rotation);
		glUseProgram(shaderProgram);
		GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
		GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
		GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &scop->model.mat[0][0]);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &scop->view.mat[0][0]);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &scop->projection.mat[0][0]);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0,  scop->size);
		glDrawElements(GL_TRIANGLES, scop->face_nb * 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
