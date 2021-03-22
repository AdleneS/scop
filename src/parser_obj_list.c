#include "scop.h"

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