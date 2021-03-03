#include "scop.h"

void load_file_obj(char *filename, t_vertex **vertex_list, t_face **face_list, t_scop *scop)
{
    FILE *file;
    int vertex_nb = 0;
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
            t_vertex *vertex = malloc(sizeof(t_vertex));
            vertex->next = NULL;
            sscanf(line, "v %f %f %f", &vertex->v.x, &vertex->v.y, &vertex->v.z);
            vertex_nb++;
            list_pushback(vertex_list, vertex);
        }

        if (strncmp(line, "vt ", 3) == 0)
            checkVt = 1;

        if (strncmp(line, "vn ", 3) == 0)
            checkVn = 1;

        if (strncmp(line, "o ", 2) == 0)
        {
            checkVn = 0;
            checkVt = 0;
        }

        if (strncmp(line, "f ", 2) == 0 && checkVt && checkVn)
        {
            t_face *face = malloc(sizeof(t_face));
            face->next = NULL;
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                   &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
                   &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
                   &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2]);
            face_nb++;
            list_pushback_face(face_list, face);
        }
        else if (strncmp(line, "f ", 2) == 0 && checkVt)
        {
            t_face *face = malloc(sizeof(t_face));
            face->next = NULL;
            sscanf(line, "f %d/%d %d/%d %d/%d",
                   &face->vertex_indices[0], &face->texture_indices[0],
                   &face->vertex_indices[1], &face->texture_indices[1],
                   &face->vertex_indices[2], &face->texture_indices[2]);
            face_nb++;
            list_pushback_face(face_list, face);
        }
        else if (strncmp(line, "f ", 2) == 0 && !checkVt && !checkVn)
        {
            t_face *face = malloc(sizeof(t_face));
            face->next = NULL;
            sscanf(line, "f %d %d %d",
                   &face->vertex_indices[0],
                   &face->vertex_indices[1],
                   &face->vertex_indices[2]);
            face_nb++;
            list_pushback_face(face_list, face);
        }
    }
    scop->size = vertex_nb;
    scop->face_nb = face_nb;
    list_to_array(scop, *vertex_list);
    list_to_array_face(scop, *face_list);
}

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

void list_to_array_face(t_scop *scop, t_face *f)
{
    t_face *tmp = f;
    int *faces;
    int i = 0;
    if (!(faces = (int *)(malloc(sizeof(int) * (scop->face_nb + 1) * 3))))
    {
        exit(1);
    }
    while (tmp)
    {
        faces[i] = tmp->vertex_indices[0] - 1;
        faces[i + 1] = tmp->vertex_indices[1] - 1;
        faces[i + 2] = tmp->vertex_indices[2] - 1;
        i += 3;
        tmp = tmp->next;
    }
    scop->faces = faces;
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