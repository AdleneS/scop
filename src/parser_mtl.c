#include "scop.h"

void load_file_mtl(char *mtl_name, t_scop *scop, char *path)
{
    (void)scop;
    FILE *file;
    char line[1024];
    strcat(path, mtl_name);
    printf("[%s]\n\n", path);
    if (!(file = fopen(path, "r"))){
        printf("error testmtl");
        return; 
    }

    while (fgets(line, 1024, file))
    {
        printf("[%s]\n", line);
    }
    fclose(file);
}
