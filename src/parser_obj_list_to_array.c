#include "scop.h"

void list_to_array(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
    //print_list(v);
    float *vertices;
    int i = 0;
    if (!(vertices = (float *)(malloc(sizeof(float) * (scop->size + 1) * 3))))
    {
        exit(1);
    }
    while (tmp)
    {
        vertices[i] = tmp->v.x;
        vertices[i + 1] = tmp->v.y;
        vertices[i + 2] = tmp->v.z;
        i += 3;
        tmp = tmp->next;
    }
    printf("%s", "VERTICE TO ARRAY DONE\n");
    scop->vertices = vertices;
}

void list_to_array_texture(t_scop *scop, t_texture *v)
{
    t_texture *tmp = v;
    //print_list(v);
    float *texture;
    int i = 0;
    if (!(texture = (float *)(malloc(sizeof(float) * (scop->textur_nb + 1) * 2))))
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
    printf("%s", "TEXTURE TO ARRAY DONE\n");
    scop->texture = texture;
}

void list_to_array_normal(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
    //print_list(v);
    float *normal;
    int i = 0;
    if (!(normal = (float *)(malloc(sizeof(float) * (scop->normal_nb + 1) * 3))))
    {
        exit(1);
    }
    while (tmp)
    {
        //dprintf(1, "%f %f %f %p\n", tmp->v.x,tmp->v.y,tmp->v.z, tmp->next);
        normal[i] = tmp->v.x;
        normal[i + 1] = tmp->v.y;
        normal[i + 2] = tmp->v.z;
        //dprintf(1, "float out\n");
        i += 3;
        tmp = tmp->next;
    }
    //dprintf(1, "end function\n");
    printf("%s", "NORMAL TO ARRAY DONE\n");
    scop->normal = normal;
}

void list_to_array_face(t_scop *scop, t_face *f)
{
    t_face *tmp = f;
    float *colors;
    int *faces_v;
    int *faces_vt;
    int *faces_vn;
    int i = 0;
    int j = 0;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    if (!(faces_v = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    if (!(faces_vn = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    if (!(faces_vt = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
        exit(1);
    if (!(colors = (float *)(malloc(sizeof(float) * (scop->face_nb + 1) * 3))))
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

        colors[i] = fmod(r, 1);
        colors[i + 1] = fmod(g, 1);
        colors[i + 2] = fmod(b, 1);
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

            colors[i] = fmod(r, 1);
            colors[i + 1] = fmod(g, 1);
            colors[i + 2] = fmod(b, 1);
            i += 3;
        }
        r += 0.05;
        g += 0.09;
        b += 0.01;
        tmp = tmp->next;
    }
    printf("%s", "FACE TO ARRAY DONE\n");
    scop->colors = colors;
    scop->faces_v = faces_v;
    scop->faces_vt = faces_vt;
    scop->faces_vn = faces_vn;
}

t_vertex_face *list_face_to_vertex(t_face *_face, t_scop *scop)
{
    t_face *list = _face;
    t_vertex_face *object = NULL;
    int j = 0;

    if (!(object = (t_vertex_face *)malloc(sizeof(t_vertex_face) * scop->face_nb * 3)))
        exit(1);

    while (list)
    {
        for (int i = 0; i < 3; i++)
        {
            object[j].vertex.x = scop->vertices[(list->vertex_indices[i] - 1) * 3];
            object[j].vertex.y = scop->vertices[(list->vertex_indices[i] - 1) * 3 + 1];
            object[j].vertex.z = scop->vertices[(list->vertex_indices[i] - 1) * 3 + 2];

            object[j].texture.x = scop->texture[(list->texture_indices[i] - 1) * 2];
            object[j].texture.y = scop->texture[(list->texture_indices[i] - 1) * 2 + 1];

            object[j].normal.x = scop->normal[(list->normal_indices[i] - 1) * 3];
            object[j].normal.y = scop->normal[(list->normal_indices[i] - 1) * 3 + 1];
            object[j].normal.z = scop->normal[(list->normal_indices[i] - 1) * 3 + 2];

            j++;
        }
        list = list->next;
    }
    printf("%s", "FACE TO VERTEX DONE\n");

    return object;
}

void set_color(t_scop **scop, t_face *face, t_material *mat)
{
    t_face *tmp = face;
    t_material *tmp_m = mat;
    float r = tmp_m->r;
    float g = tmp_m->g;
    float b = tmp_m->b;
    int i = 0;
    int current_mat = tmp->texture_index;
    if (!((*scop)->colors = (float *)(malloc(sizeof(float) * ((*scop)->face_nb) * 9))))
        exit(1);
    while (tmp)
    {
        if (tmp->texture_index != current_mat)
        {
            r = tmp_m->r;
            g = tmp_m->g;
            b = tmp_m->b;
            current_mat = tmp->texture_index;
            tmp_m = tmp_m->next;
        }
        (*scop)->colors[i] = r;
        (*scop)->colors[i + 1] = g;
        (*scop)->colors[i + 2] = b;
        (*scop)->colors[i + 3] = r;
        (*scop)->colors[i + 4] = g;
        (*scop)->colors[i + 5] = b;
        (*scop)->colors[i + 6] = r;
        (*scop)->colors[i + 7] = g;
        (*scop)->colors[i + 8] = b;

        i += 9;
        tmp = tmp->next;
    }
    printf("%s", "SET COLOR DONE\n");
}