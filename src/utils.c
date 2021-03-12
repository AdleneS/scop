#include "scop.h"

void mat4x4_print(t_mat4 m)
{
    int i = -1;
    while (++i < 4)
    {
        int j = -1;
        while (++j < 4)
        {
            printf("| %f |", m.mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

float min(float a, float b)
{
    return ((a < b) ? a : b);
}

float max(float a, float b)
{
    return ((a > b) ? a : b);
}

float clamp(float a, float mi, float ma)
{
    return (min(max(a, mi), ma));
}

t_mat4 v_add(t_vec3 v2)
{
    t_mat4 new;
    init_mat4(&new);
    new.mat[3][0] = v2.x;
    new.mat[3][1] = v2.y;
    new.mat[3][2] = v2.z;
    return ((new));
}

void mat4x4_perspective(t_mat4 *m, float y_fov, float aspect, float n, float f)
{
    float const a = 1.f / (float)tan(y_fov / 2.f);

    m->mat[0][0] = a / aspect;
    m->mat[0][1] = 0.f;
    m->mat[0][2] = 0.f;
    m->mat[0][3] = 0.f;

    m->mat[1][0] = 0.f;
    m->mat[1][1] = a;
    m->mat[1][2] = 0.f;
    m->mat[1][3] = 0.f;

    m->mat[2][0] = 0.f;
    m->mat[2][1] = 0.f;
    m->mat[2][2] = -((f + n) / (f - n));
    m->mat[2][3] = -1.f;

    m->mat[3][0] = 0.f;
    m->mat[3][1] = 0.f;
    m->mat[3][2] = -((2.f * f * n) / (f - n));
    m->mat[3][3] = 0.f;
}

// GLfloat *flat_matrice(t_mat4 mat)
// {
//     GLfloat flat[16];
//     int n = 0;
//     int i = -1;
//     while (++i < 4)
//     {
//         int j = -1;
//         while (++j < 4)
//         {
//             flat[n] = mat.mat[i][j];
//             n++;
//         }
//     }
//     return flat;
// }
//
// t_mat4 v_sub(t_mat4 v1, t_mat4 v2)
// {
// return ((t_mat4){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
// }
//
// t_mat4 v_mul(t_mat4 v1, t_mat4 v2)
// {
// return ((t_mat4){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
// }
//
// t_mat4 v_mulk(t_mat4 v1, float k)
// {
// return ((t_mat4){v1.x * k, v1.y * k, v1.z * k});
// }
// t_mat4 v_div(t_mat4 v1, float k)
// {
// return ((t_mat4){v1.x / k, v1.y / k, v1.z / k});
// }

t_mat4 mat4x4_mult(t_mat4 a, t_mat4 b)
{
    t_mat4 temp;
    int k, r, c;
    for (c = 0; c < 4; ++c)
        for (r = 0; r < 4; ++r)
        {
            temp.mat[c][r] = 0.f;
            for (k = 0; k < 4; ++k)
                temp.mat[c][r] += a.mat[k][r] * b.mat[c][k];
        }
    return (temp);
}

t_mat4 mat4x4_rotx(t_mat4 in, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    t_mat4 R = (t_mat4){{{1.f, 0.f, 0.f, 0.f},
                         {0.f, c, s, 0.f},
                         {0.f, -s, c, 0.f},
                         {0.f, 0.f, 0.f, 1.f}}};
    return (mat4x4_mult(in, R));
}

t_mat4 mat4x4_roty(t_mat4 in, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    t_mat4 R = {{{c, 0.f, s, 0.f},
                 {0.f, 1.f, 0.f, 0.f},
                 {-s, 0.f, c, 0.f},
                 {0.f, 0.f, 0.f, 1.f}}};
    return (mat4x4_mult(in, R));
}

t_mat4 mat4x4_rotz(t_mat4 in, float angle)
{
    float s = sinf(angle);
    float c = cosf(angle);
    t_mat4 R = (t_mat4){{{c, s, 0.f, 0.f},
                         {-s, c, 0.f, 0.f},
                         {0.f, 0.f, 1.f, 0.f},
                         {0.f, 0.f, 0.f, 1.f}}};
    return (mat4x4_mult(in, R));
}

// void rot_x(t_param *p, t_mat4 *d)
// {
//     t_mat4 new;

//     new.x = d->x;
//     new.y = d->y *cosf(p->cam.rot.x) - d->z *sinf(p->cam.rot.x);
//     new.z = d->y *sinf(p->cam.rot.x) + d->z *cosf(p->cam.rot.x);
//     *d = new;
// }

// void rot_y(t_param *p, t_mat4 *d)
// {
//     t_mat4 new;

//     new.x = d->x *cosf(p->cam.rot.y) + d->z *sinf(p->cam.rot.y);
//     new.y = d->y;
//     new.z = d->x * -sinf(p->cam.rot.y) + d->z *cosf(p->cam.rot.y);
//     *d = new;
// }

// float v_dotproduct(t_mat4 v1, t_mat4 v2)
// {
//     return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
// }

// float v_length(t_mat4 v)
// {
//     return (sqrtf(v_dotproduct(v, v)));
// }

// t_mat4 v_normalize(t_mat4 v)
// {
//     float l = v_length(v);
//     return ((t_mat4){v.x / l, v.y / l, v.z / l});
// }

// t_mat4 v_crossprod(t_mat4 v1, t_mat4 v2)
// {
//     t_mat4 v;

//     v.x = v1.y * v2.z - v1.z * v2.y;
//     v.y = v1.z * v2.x - v1.x * v2.z;
//     v.z = v1.x * v2.y - v1.y * v2.x;
//     return (v);
// }

void init_mat4(t_mat4 *s)
{
    int i = -1;
    while (++i < 4)
    {
        int j = -1;
        while (++j < 4)
        {
            s->mat[i][j] = 0.0f;
        }
    }
    s->mat[0][0] = 1.0f;
    s->mat[1][1] = 1.0f;
    s->mat[2][2] = 1.0f;
    s->mat[3][3] = 1.0f;
}

void print_array(float *a, int s)
{
    int i = 0;
    while (i < s)
    {
        if (i % 3 == 0)
            printf("\n");
        printf("%f ", a[i]);
        i++;
    }
    printf("\n");
}

void print_array_vt(float *a, int s)
{
    int i = 0;
    while (i < s)
    {
        if (i % 2 == 0)
            printf("\n");

        printf("%f ", a[i]);
        i++;
    }
    printf("\n");
}

void print_array_vn(float *a, int s)
{
    int i = 0;
    while (i < s)
    {
        if (i % 3 == 0)
            printf("\n");

        printf("%f ", a[i]);
        i++;
    }
    printf("\n");
}

void print_array_face_vt(int *a, int s)
{
    int i = 0;
    while (i < s)
    {
        if (i % 2 == 0)
            printf("\n");
        printf("%d ", a[i]);
        i++;
    }
    printf("\n");
}

void print_array_face(int *a, int s)
{
    int i = 0;
    while (i < s)
    {
        if (i % 3 == 0)
            printf("\n");
        printf("%d ", a[i]);
        i++;
    }
    printf("\n");
}

void print_list_v(t_vertex *list)
{
    t_vertex *tmp;

    tmp = list;
    int i = 0;
    while (tmp != NULL)
    {
        printf("v %f  %f  %f\n", tmp->v.x, tmp->v.y, tmp->v.z);
        i++;
        tmp = tmp->next;
    }
    printf("%d/n/n", i);
}

void print_list_vt(t_texture *list)
{
    t_texture *tmp;

    tmp = list;
    int i = 0;
    while (tmp != NULL)
    {
        printf("vt %f  %f\n", tmp->v.x, tmp->v.y);
        i++;
        tmp = tmp->next;
    }
    printf("%d/n/n", i);
}

void print_list_vn(t_vertex *list)
{
    t_vertex *tmp;

    tmp = list;
    int i = 0;
    while (tmp != NULL)
    {
        printf("vn %f  %f  %f\n", tmp->v.x, tmp->v.y, tmp->v.z);
        i++;
        tmp = tmp->next;
    }
    printf("%d/n/n", i);
}

void print_list_face(t_face *list)
{
    t_face *tmp;

    tmp = list;
    int i = 0;
    while (tmp != NULL)
    {
        if (tmp->n_face == 4)
        {
            printf("f %d  %d  %d  %d\n", tmp->vertex_indices[0], tmp->vertex_indices[1], tmp->vertex_indices[2], tmp->vertex_indices[3]);
        }
        else
        {
            printf("f %d  %d  %d\n", tmp->vertex_indices[0], tmp->vertex_indices[1], tmp->vertex_indices[2]);
        }
        i++;
        tmp = tmp->next;
    }
    printf("\n\n");
}

void print_list_face_obj(t_scop *scop)
{
    for (int i = 0; i < (scop->face_nb * 3); i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            printf("\n");
        }
        printf("%d/%d/%d  ", scop->faces_v[i] + 1, scop->faces_vt[i] + 1, scop->faces_vn[i] + 1);
    }
}

void print_list_shader(t_shader tmp)
{
    printf("shader file fragmentShaderLight :: \n%s\n\n\n", tmp.fragmentShaderLight);
    printf("shader file vertexShaderLight :: \n%s\n\n\n", tmp.vertexShaderLight);
    printf("shader file fragmentShaderSource :: \n%s\n\n\n", tmp.fragmentShaderSource);
    printf("shader file vertexShaderSource :: \n%s\n\n\n", tmp.vertexShaderSource);
}

void print_vertex_face(t_vertex_face *list)
{
    while (list->next)
    {
        printf("v %f %f %f\n", list->vertex.x, list->vertex.y, list->vertex.z);
        printf("t %f %f\n", list->texture.x, list->texture.y);
        printf("n %f %f %f\n\n", list->normal.x, list->normal.y, list->normal.z);
        list = list->next;
    }
}
