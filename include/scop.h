#ifndef SCOP_H
#define SCOP_H
#include <fcntl.h>
#include <stdio.h>
#include <libc.h>
#include "math.h"
#include <sys/types.h>
#include <dirent.h>
#include "../gl3w/include/GL/gl3w.h"
#include "../glfw-3.3.2/include/GLFW/glfw3.h"

typedef struct dirent t_dirent;

typedef struct s_vector2f
{
    float x;
    float y;
} t_vector2f;

typedef struct s_vector3f
{
    float x;
    float y;
    float z;
} t_vector3f;
typedef struct s_vec3
{
    float x;
    float y;
    float z;
    float w;
} t_vec3;
typedef struct s_mat4
{
    float mat[4][4];
} t_mat4;

typedef struct s_vertex_face
{
    t_vector3f vertex;
    t_vector2f texture;
    t_vector3f normal;
} t_vertex_face;

typedef struct s_material
{
    char texture_name[32];
    float r;
    float g;
    float b;
} t_material;

typedef struct s_mtl
{
    char *newmtl;
    t_vec3 Kd;
    struct s_mtl *next;
} t_mtl;

typedef struct s_vertex
{
    t_vec3 v;
} t_vertex;

typedef struct s_normal
{
    t_vec3 v;
} t_normal;

typedef struct s_texture
{
    t_vector2f v;
} t_texture;

typedef struct s_face
{
    int n_face;
    int texture_index;
    char texture_name[32];
    int vertex_indices[4];
    int texture_indices[4];
    int normal_indices[4];
} t_face;

typedef struct s_shader
{
    char *vertexShaderSource;
    char *fragmentShaderSource;
    char *vertexShaderLight;
    char *fragmentShaderLight;
} t_shader;

typedef struct s_scop
{
    t_vec3 pos;
    t_vec3 rot;
    t_mat4 model;
    t_mat4 view;
    t_mat4 projection;
    t_vertex *vertices;
    float *colors;
    float *colorsFace;
    t_texture *texture;
    t_normal *normal;
    int *faces_v;
    int *faces_vt;
    int *faces_vn;
    int size;
    int vertex_nb;
    int face_nb;
    int texture_nb;
    int normal_nb;
    int material_nb;
    int faceColors;
    unsigned short int lightStop;
    t_vertex_face *object;
} t_scop;

t_mat4 mat4x4_rotx(t_mat4 in, float angle);
t_mat4 mat4x4_roty(t_mat4 in, float angle);
t_mat4 mat4x4_rotz(t_mat4 in, float angle);
t_mat4 mat4x4_mult(t_mat4 a, t_mat4 b);

t_mat4 v_sub(t_mat4 v1, t_mat4 v2);
float v_dotproduct(t_mat4 v1, t_mat4 v2);
t_mat4 v_mul(t_mat4 v1, t_mat4 v2);
t_mat4 v_add(t_vec3 v2);
t_mat4 v_normalize(t_mat4 v);
t_mat4 v_sub(t_mat4 v1, t_mat4 v2);
t_mat4 v_mulk(t_mat4 v1, float k);
float v_length(t_mat4 v);
t_mat4 v_div(t_mat4 v1, float k);
void rot_x(t_mat4 *vec, t_mat4 *d);
void init_mat4(t_mat4 *s);
GLfloat *flat_matrice(t_mat4 mat);
void mat4x4_perspective(t_mat4 *m, float y_fov, float aspect, float n, float f);
void mat4x4_print(t_mat4 m);
void load_file_obj(char *filename, t_scop *scop);
void print_array_vn(float *a, int s);

void list_pushback(t_vertex **head, t_vertex *new);
void print_list_v(t_vertex *list);
void list_to_array(t_scop *scop, t_vertex *v);
void print_array_vertex(t_vertex *a, int s);
void list_pushback_face(t_face **head, t_face *new);
void print_list_face(t_face *list);
void list_to_array_face(t_scop *scop, t_face *f);
void print_array_face(int *a, int s);
void list_pushback_tex(t_texture **head, t_texture *new);
int count_char_in_string(char *str, char c);
void print_list_vn(t_vertex *list);
void print_list_vt(t_texture *list);
void print_array_vt(float *a, int s);
void list_to_array_texture(t_scop *scop, t_texture *v);
void list_to_array_normal(t_scop *scop, t_vertex *v);
void print_array_face_vt(int *a, int s);
void print_list_face_obj(t_scop *scop);
t_material *load_file_mtl(char *mtl_name, t_scop *scop, char *path);

t_shader read_path();
char *sort_path(char *path);
char *join(const char *s1, const char *s2);
void list_pushback_shader(t_shader **head, t_shader *new);
void print_list_shader(t_shader tmp);
unsigned int compile_shader_test(char *vertexSource, char *fragmentSource);

void input_key(t_scop *scop, GLFWwindow *window);
void print_vertex_face(t_vertex_face *object, int size);
t_vertex_face *list_face_to_vertex(t_face *list, t_scop *scop);
void set_color(t_scop **scop, t_face *face, t_material *mat);
GLuint loadTex(const char *imagePath);
void list_pushback_mat(t_material **head, t_material *new);
void print_list_material(t_material *list);
void set_color_per_face(t_scop **scop);

#endif
