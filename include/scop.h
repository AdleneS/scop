#ifndef SCOP_H
#define SCOP_H
#include <fcntl.h>
#include <stdio.h>
#include "../minilibx/mlx.h"
#include "math.h"
#include "../gl3w/include/GL/gl3w.h"
#include "../glfw-3.3.2/include/GLFW/glfw3.h"
typedef struct s_vector3f
{
    float x;
    float y;
    float z;
} t_vector3f;

typedef struct s_scop
{
    GLuint VBO;
} t_scop;

typedef struct s_vec3
{
    double x;
    double y;
    double z;
    double w;
} t_vec3;

typedef struct s_mat4
{
    float mat[4][4];
} t_mat4;

t_mat4 vrot(t_mat4 in, t_mat4 angle);
t_mat4 v_sub(t_mat4 v1, t_mat4 v2);
double v_dotproduct(t_mat4 v1, t_mat4 v2);
t_mat4 v_mul(t_mat4 v1, t_mat4 v2);
t_mat4 v_add(t_mat4 mat, t_vec3 v2);
t_mat4 v_normalize(t_mat4 v);
t_mat4 v_sub(t_mat4 v1, t_mat4 v2);
t_mat4 v_mulk(t_mat4 v1, double k);
double v_length(t_mat4 v);
t_mat4 v_div(t_mat4 v1, double k);
void rot_x(t_mat4 *vec, t_mat4 *d);
void init_mat4(t_mat4 *s);
GLfloat *flat_matrice(t_mat4 mat);

#endif
