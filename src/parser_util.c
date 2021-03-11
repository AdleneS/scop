#include "scop.h"

static int path_len(char *str)
{
    int i = 0;
    while (str[i++])
    {
        ;
    }
    return i;
}

char *sort_path(char *path)
{
    char *_path;
    int tmp = 0;
    if (!(_path = (char *)malloc(sizeof(char) * path_len(path) + 1)))
        return NULL;

    for (int i = 0; path[i]; i++)
    {
        if (path[i] == '/' && path[i])
        {
            tmp = i;
        }
    }
    strncpy(_path, path, tmp + 1);
    return _path;
}

char *join(const char *s1, const char *s2)
{
    char *result;
    if (!(result = (char *)malloc(strlen(s1) + strlen(s2) + 1)))
        return NULL;

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }

    return result;
}