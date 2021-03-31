#include "scop.h"

t_vertex_face *list_face_to_vertex(t_face *face, t_scop *scop)
{
    int j = 0;
    int face_i = 0;
    t_vertex_face *object = NULL;
    if (!(object = (t_vertex_face *)malloc(sizeof(t_vertex_face) * scop->face_nb * 3)))
        exit(1);

    while (face_i < scop->face_nb)
    {
        for (int i = 0; i < 3; i++)
        {
            if (scop->vertex_nb && (face[face_i].vertex_indices[i]) <= scop->vertex_nb)
            {
                object[j].vertex.x = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.x;
                object[j].vertex.y = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.y;
                object[j].vertex.z = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.z;
            }
            else
                exit(1);
            if (scop->texture_nb)
            {
                if (face[face_i].texture_indices[i] > scop->texture_nb)
                    exit(1);
                object[j].texture.x = scop->texture[(face[face_i].texture_indices[i] - 1)].v.x;
                object[j].texture.y = scop->texture[(face[face_i].texture_indices[i] - 1)].v.y;
            }
            else
            {
                if (i == 0)
                {
                    object[j].texture.x = 1.0;
                    object[j].texture.y = 1.0;
                }
                if (i == 1)
                {
                    object[j].texture.x = 0.0;
                    object[j].texture.y = 1.0;
                }
                if (i == 2)
                {
                    object[j].texture.x = 1.0;
                    object[j].texture.y = 0.0;
                }
            }
            if (scop->normal_nb)
            {
                if (face[face_i].normal_indices[i] > scop->normal_nb)
                    exit(1);
                object[j].normal.x = scop->normal[(face[face_i].normal_indices[i] - 1)].v.x;
                object[j].normal.y = scop->normal[(face[face_i].normal_indices[i] - 1)].v.y;
                object[j].normal.z = scop->normal[(face[face_i].normal_indices[i] - 1)].v.z;
            }
            j++;
        }
        face_i++;
    }
    printf("%s", "\033[0;33m✓ \033[0;32mFACE TO VERTEX DONE\n\033[0;37m");

    return object;
}

void set_color(t_scop **scop, t_face *face, t_material *mat)
{
    float r = 0;
    float g = 0;
    float b = 0;
    int i = 0;
    int face_i = 0;
    int current_mat = -1;
    if (!((*scop)->colors = (float *)(malloc(sizeof(float) * ((*scop)->face_nb) * 9))))
        exit(1);
    while (face_i < (*scop)->face_nb)
    {
        if (face[face_i].texture_index != current_mat)
        {
            current_mat = face[face_i].texture_index;

            for (int j = 0; j < (*scop)->material_nb; j++)
            {
                if (strcmp(mat[j].texture_name, face[face_i].texture_name) == 0)
                {
                    r = mat[j].r;
                    g = mat[j].g;
                    b = mat[j].b;
                    break;
                }
            }
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
        face_i++;
    }
    printf("%s", "\033[0;33m✓ \033[0;32mSET COLOR DONE\n\033[0;37m");
}

void set_color_per_face(t_scop **scop)
{
    float r = 0.5;
    float g = 0.5;
    float b = 0.5;
    int i = 0;
    int face_i = 0;
    if (!((*scop)->colorsFace = (float *)(malloc(sizeof(float) * ((*scop)->face_nb) * 9))))
        exit(1);
    while (face_i < (*scop)->face_nb)
    {

        (*scop)->colorsFace[i] = fmod(r, 1);
        (*scop)->colorsFace[i + 1] = fmod(g, 1);
        (*scop)->colorsFace[i + 2] = fmod(b, 1);
        (*scop)->colorsFace[i + 3] = fmod(r, 1);
        (*scop)->colorsFace[i + 4] = fmod(g, 1);
        (*scop)->colorsFace[i + 5] = fmod(b, 1);
        (*scop)->colorsFace[i + 6] = fmod(r, 1);
        (*scop)->colorsFace[i + 7] = fmod(g, 1);
        (*scop)->colorsFace[i + 8] = fmod(b, 1);

        r += 0.02;
        g += 0.05;
        b += 0.08;
        i += 9;
        face_i++;
    }
    printf("%s", "\033[0;33m✓ \033[0;32mSET COLOR DONE\n\033[0;37m");
}