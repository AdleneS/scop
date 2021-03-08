#include "scop.h"

void load_file_mtl(char *mtl_name, t_scop *scop)
{
    (void)scop;
    FILE *file;
    char line[1024];
    char dest[40] = "./assets/";
    strcat(dest, mtl_name);
    printf("[%s]\n\n", dest);
    if (!(file = fopen(dest, "r")))
        exit(1);

    while (fgets(line, 1024, file))
    {
        printf("%s\n", line);
    }
    fclose(file);
}
