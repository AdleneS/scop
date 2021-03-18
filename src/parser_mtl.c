#include "scop.h"

t_material *load_file_mtl(char *mtl_name, t_scop *scop, char *path)
{
    (void)scop;
    t_material *materials = NULL;
    FILE *file;
    char line[1024];
    strcat(path, mtl_name);
    //printf("[%s]\n", path);
    if (!(file = fopen(path, "r")))
    {
        printf("error testmtl\n");
        return NULL;
    }

    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "Kd", 2) == 0)
        {
            t_material *mat;
            if (!(mat = malloc(sizeof(t_material))))
            {
                exit(1);
            }
            mat->next = NULL;
            sscanf(line, "Kd %f %f %f", &mat->r, &mat->g, &mat->b);
            list_pushback_mat(&materials, mat);
        }
    }
    fclose(file);
    return materials;
}
