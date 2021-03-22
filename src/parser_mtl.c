#include "scop.h"

int get_size_mtl(char *path)
{
    FILE *file;
    char line[1024];
    int texture_nb = 0;
    if (!(file = fopen(path, "r")))
    {
        printf("Cannot open mtl\n");
        return 0;
    }

    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "# Material Count:", 17) == 0)
        {
            sscanf(line, "# Material Count: %d", &texture_nb);
            return texture_nb;
        }
        if (strncmp(line, "#", 1) != 0)
        {
            return 0;
        }
    }
    fclose(file);
    return 0;
}

t_material *load_file_mtl(char *mtl_name, t_scop *scop, char *path)
{
    strcat(path, mtl_name);
    t_material *materials;
    FILE *file;
    char line[1024];
    int texture_nb = get_size_mtl(path);
    int i_newmtl = 0;

    if (!(materials = malloc(sizeof(t_material) * texture_nb)))
        exit(1);
    if (!(file = fopen(path, "r")))
    {
        printf("error testmtl\n");
        return NULL;
    }
    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "newmtl", 6) == 0)
        {
            sscanf(line, "newmtl %s", &materials[i_newmtl].texture_name[0]);
        }
        if (strncmp(line, "Kd", 2) == 0)
        {
            sscanf(line, "Kd %f %f %f", &materials[i_newmtl].r, &materials[i_newmtl].g, &materials[i_newmtl].b);
            i_newmtl++;
        }
    }
    scop->material_nb = texture_nb;
    fclose(file);
    return materials;
}
