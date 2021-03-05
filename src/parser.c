#include "scop.h"

void load_file_obj(char *filename, t_scop *scop)
{
    FILE *file;
    t_vertex *vertex_list = NULL;
    t_vertex *normal_list = NULL;
    t_texture *textur_list = NULL;
    t_face *face_list = NULL;

    int vertex_nb = 0;
    int texture_nb = 0;
    int normal_nb = 0;
    int face_nb = 0;
    short int checkVn = 0;
    short int checkVt = 0;
    if (!(file = fopen(filename, "r")))
        exit(1);

    char line[1024];

    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "v ", 2) == 0)
        {
            if (checkVn || checkVt)
            {
                checkVn = 0;
                checkVt = 0;
            }
            t_vertex *vertex = malloc(sizeof(t_vertex));
            vertex->next = NULL;
            sscanf(line, "v %f %f %f", &vertex->v.x, &vertex->v.y, &vertex->v.z);
            vertex_nb++;
            list_pushback(&vertex_list, vertex);
        }

        if (strncmp(line, "vt ", 3) == 0)
        {
            t_texture *texture = malloc(sizeof(t_texture));
            texture->next = NULL;
            sscanf(line, "vt %f %f", &texture->v.x, &texture->v.y);
            texture_nb++;
            list_pushback_tex(&textur_list, texture);
            checkVt = 1;
        }

        if (strncmp(line, "vn ", 3) == 0)
        {
            t_vertex *normal = malloc(sizeof(t_vertex));
            normal->next = NULL;
            sscanf(line, "vn %f %f %f", &normal->v.x, &normal->v.y, &normal->v.z);
            normal_nb++;
            list_pushback(&normal_list, normal);
            checkVt = 1;
            checkVn = 1;
        }

        if (strncmp(line, "f ", 2) == 0)
        {
            if (checkVt && checkVn)
            {
                t_face *face = malloc(sizeof(t_face));
                face->next = NULL;

                if (count_char_in_string(line, ' ') >= 4)
                {
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2],
                           &face->vertex_indices[3], &face->texture_indices[3], &face->normal_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else
                {
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2]);
                    face->n_face = 3;
                }
                face_nb++;
                list_pushback_face(&face_list, face);
            }

            else if (checkVt)
            {
                t_face *face = malloc(sizeof(t_face));
                face->next = NULL;

                if (count_char_in_string(line, ' ') >= 4)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2],
                           &face->vertex_indices[3], &face->texture_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2]);
                    face->n_face = 3;
                }
                face_nb++;
                list_pushback_face(&face_list, face);
            }

            else if (checkVn)
            {
                t_face *face = malloc(sizeof(t_face));
                face->next = NULL;

                if (count_char_in_string(line, ' ') >= 4)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->normal_indices[2],
                           &face->vertex_indices[3], &face->normal_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->normal_indices[2]);
                    face->n_face = 3;
                }
                face_nb++;
                list_pushback_face(&face_list, face);
            }

            else if (!checkVt && !checkVn)
            {
                t_face *face = malloc(sizeof(t_face));
                face->next = NULL;

                if (count_char_in_string(line, ' ') >= 4)
                {
                    sscanf(line, "f %d %d %d %d",
                           &face->vertex_indices[0],
                           &face->vertex_indices[1],
                           &face->vertex_indices[2],
                           &face->vertex_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else
                {
                    sscanf(line, "f %d %d %d",
                           &face->vertex_indices[0],
                           &face->vertex_indices[1],
                           &face->vertex_indices[2]);
                    face->n_face = 3;
                }
                face_nb++;
                list_pushback_face(&face_list, face);
            }
        }
    }

    scop->size = vertex_nb;
    scop->textur_nb = texture_nb;
    scop->normal_nb = normal_nb;
    scop->face_nb = face_nb;
    list_to_array(scop, vertex_list);
    list_to_array_face(scop, face_list);

    //print_list_v(vertex_list);
    //print_list_vt(textur_list);
    //print_list_vn(normal_list);
    //print_list_face(face_list);
}

void list_to_array(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
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
    scop->vertices = vertices;
}

void list_to_array_face(t_scop *scop, t_face *f)
{
    t_face *tmp = f;
    int *faces;
    float *colors;
    int i = 0;
    float r = 0;
    float g = 0;
    float b = 0;
    if (!(faces = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
    {
        exit(1);
    }
    if (!(colors = (float *)(malloc(sizeof(float) * (scop->face_nb + 1) * 3))))
    {
        exit(1);
    }
    while (tmp)
    {
        //printf("%d  %d  %f\n", scop->face_nb, i / 3, (float)(((i + 3) / 3) / (float)scop->face_nb));
        faces[i] = tmp->vertex_indices[0] - 1;
        faces[i + 1] = tmp->vertex_indices[1] - 1;
        faces[i + 2] = tmp->vertex_indices[2] - 1;
        colors[i] = fmod(r, 1);
        colors[i + 1] = fmod(g, 1);
        colors[i + 2] = fmod(b, 1);
        i += 3;

        if (tmp->n_face == 4)
        {
            faces[i] = tmp->vertex_indices[2] - 1;
            faces[i + 1] = tmp->vertex_indices[3] - 1;
            faces[i + 2] = tmp->vertex_indices[0] - 1;
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
    scop->faces = faces;
    scop->colors = colors;
}

void list_pushback(t_vertex **head, t_vertex *new)
{
    t_vertex *tmp_v;
    if (!*head)
        *head = new;
    else
    {
        tmp_v = *head;
        while (tmp_v->next)
            tmp_v = tmp_v->next;
        tmp_v->next = new;
    }
}

void list_pushback_tex(t_texture **head, t_texture *new)
{
    t_texture *tmp_v;
    if (!*head)
        *head = new;
    else
    {
        tmp_v = *head;
        while (tmp_v->next)
            tmp_v = tmp_v->next;
        tmp_v->next = new;
    }
}

void list_pushback_face(t_face **head, t_face *new)
{
    t_face *tmp_f;
    if (!*head)
        *head = new;
    else
    {
        tmp_f = *head;
        while (tmp_f->next)
            tmp_f = tmp_f->next;
        tmp_f->next = new;
    }
}

int count_char_in_string(char *str, char c)
{
    int len = 0;

    for (int i = 0; str[i]; i++)
    {
        if (str[i] == c && str[i + 1] != '\n')
        {
            len++;
        }
    }
    return len;
}