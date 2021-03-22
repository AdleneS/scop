#include "scop.h"

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

// void list_pushback_mat(t_material **head, t_material *new)
// {
//     t_material *tmp_m;
//     if (!*head)
//         *head = new;
//     else
//     {
//         tmp_m = *head;
//         while (tmp_m->next)
//             tmp_m = tmp_m->next;
//         tmp_m->next = new;
//     }
// }

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