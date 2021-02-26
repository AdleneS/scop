#include "scop.h"

void load_file_obj(char *filename, t_vertex **vertex_list, t_scop *scop)
{
    FILE *file;
    int size = 0;
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
            size++;
            list_pushback(vertex_list, vertex);
        }
    }
    scop->size = size;
    list_to_array(scop, *vertex_list);
}

void list_to_array(t_scop *scop, t_vertex *v)
{
    t_vertex *tmp = v;
    //print_list(v);
    float *vertices;
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
        vertices[i + 3] = 0 + i % 5;
        vertices[i + 4] = 0 + i % 9;
        vertices[i + 5] = 0 + i % 2;
        i += 6;
        tmp = tmp->next;
    }
    scop->vertices = vertices;
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