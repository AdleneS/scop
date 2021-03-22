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
            //printf("%f\n ", scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.x);
            object[j].vertex.x = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.x;
            object[j].vertex.y = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.y;
            object[j].vertex.z = scop->vertices[(face[face_i].vertex_indices[i] - 1)].v.z;

            object[j].texture.x = scop->texture[(face[face_i].texture_indices[i] - 1)].v.x;
            object[j].texture.y = scop->texture[(face[face_i].texture_indices[i] - 1)].v.y;

            object[j].normal.x = scop->normal[(face[face_i].normal_indices[i] - 1)].v.x;
            object[j].normal.y = scop->normal[(face[face_i].normal_indices[i] - 1)].v.y;
            object[j].normal.z = scop->normal[(face[face_i].normal_indices[i] - 1)].v.z;
            j++;
        }
        face_i++;
    }
    printf("%s", "FACE TO VERTEX DONE\n");

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
    printf("%s", "SET COLOR DONE\n");
}