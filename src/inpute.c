#include "scop.h"

void input_key(t_scop *scop, GLFWwindow *window)
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		scop->pos.y += 0.5;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		scop->pos.y -= 0.5;
    double xpos, ypos;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        printf("x = %f ; y = %f || scop x = %f ; scop y = %f\n", xpos, ypos, scop->pos.x, scop->pos.x);
    }
}