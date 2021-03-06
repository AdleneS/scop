#include "scop.h"

void list_to_array(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
    //print_list(v);
    float *vertices;
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    int i = 0;
    if (!(vertices = (float *)(malloc(sizeof(float) * (scop->size + 1) * 6))))
    {
        exit(1);
    }
    while (tmp)
    {
        vertices[i] = tmp->v.x;
        vertices[i + 1] = tmp->v.y;
        vertices[i + 2] = tmp->v.z;
        vertices[i + 3] = fmod(r, 1);
        vertices[i + 4] = fmod(g, 1);
        vertices[i + 5] = fmod(b, 1);
        i += 6;
        r += 0.05;
        g += 0.09;
        b += 0.01;
        tmp = tmp->next;
    }
    scop->vertices = vertices;
}

void list_to_array_texture(t_scop *scop, t_texture *v)
{
    t_texture *tmp = v;
    //print_list(v);
    float *texture;
    int i = 0;
    if (!(texture = (float *)(malloc(sizeof(float) * (scop->size + 1) * 6))))
    {
        exit(1);
    }
    while (tmp)
    {
        texture[i] = tmp->v.x;
        texture[i + 1] = tmp->v.y;
        i += 2;
        tmp = tmp->next;
    }
    scop->texture = texture;
}

void list_to_array_normal(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
    //print_list(v);
    float *normal;
    int i = 0;
    if (!(normal = (float *)(malloc(sizeof(float) * (scop->size + 1) * 6))))
    {
        exit(1);
    }
    while (tmp)
    {
        normal[i] = tmp->v.x;
        normal[i + 1] = tmp->v.y;
        normal[i + 2] = tmp->v.z;
        i += 3;
        tmp = tmp->next;
    }
    scop->normal = normal;
}

void list_to_array_face(t_scop *scop, t_face *f)
{
    t_face *tmp = f;
    int *faces_v;
    int *faces_vt;
    int *faces_vn;
    int i = 0;
    int j = 0;

    if (!(faces_v = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    if (!(faces_vn = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    if (!(faces_vt = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    while (tmp)
    {
        faces_v[i] = tmp->vertex_indices[0] - 1;
        faces_v[i + 1] = tmp->vertex_indices[1] - 1;
        faces_v[i + 2] = tmp->vertex_indices[2] - 1;

        faces_vt[i] = tmp->texture_indices[0] - 1;
        faces_vt[i + 1] = tmp->texture_indices[1] - 1;
        faces_vt[i + 2] = tmp->texture_indices[2] - 1;

        faces_vn[i] = tmp->normal_indices[0] - 1;
        faces_vn[i + 1] = tmp->normal_indices[1] - 1;
        faces_vn[i + 2] = tmp->normal_indices[2] - 1;
        i += 3;
        j += 2;

        if (tmp->n_face == 4)
        {
            faces_v[i] = tmp->vertex_indices[2] - 1;
            faces_v[i + 1] = tmp->vertex_indices[3] - 1;
            faces_v[i + 2] = tmp->vertex_indices[0] - 1;

            faces_vt[i] = tmp->texture_indices[2] - 1;
            faces_vt[i + 1] = tmp->texture_indices[3] - 1;
            faces_vt[i + 2] = tmp->texture_indices[0] - 1;

            faces_vn[i] = tmp->normal_indices[2] - 1;
            faces_vn[i + 1] = tmp->normal_indices[3] - 1;
            faces_vn[i + 2] = tmp->normal_indices[0] - 1;
            i += 3;
        }

        tmp = tmp->next;
    }
    scop->faces_v = faces_v;
    scop->faces_vt = faces_vt;
    scop->faces_vn = faces_vn;
}