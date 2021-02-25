#ifndef SCOP_H
#define SCOP_H
#include <fcntl.h>
#include <stdio.h>
#include "math.h"
#include "../gl3w/include/GL/gl3w.h"
#include "../glfw-3.3.2/include/GLFW/glfw3.h"
typedef struct s_vector3f
{
    float x;
    float y;
    float z;
} t_vector3f;
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
typedef struct s_scop
{
    t_vec3 pos;
    t_vec3 rot;
    t_mat4 model;
    t_mat4 view;
    t_mat4 projection;
} t_scop;

t_mat4 mat4x4_rotx(t_mat4 in, float angle);
t_mat4 mat4x4_roty(t_mat4 in, float angle);
t_mat4 mat4x4_rotz(t_mat4 in, float angle);
t_mat4 mat4x4_mult(t_mat4 a, t_mat4 b);
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
void mat4x4_perspective(t_mat4 *m, float y_fov, float aspect, float n, float f);
void mat4x4_print(t_mat4 m);

#endif
