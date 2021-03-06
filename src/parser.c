#include "scop.h"

void file_obj_size(char *filename, t_scop *scop)
{
    FILE *file;

    int texture_nb = 0;
    int vertex_nb = 0;
    int normal_nb = 0;
    int face_nb = 0;

    if (!(file = fopen(filename, "r")))
        exit(1);

    char line[1024];

    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "v ", 2) == 0)
            vertex_nb++;
        if (strncmp(line, "vt ", 3) == 0)
            texture_nb++;
        if (strncmp(line, "vn ", 3) == 0)
            normal_nb++;
        if (strncmp(line, "f ", 2) == 0)
            count_char_in_string(line, ' ') >= 4 ? face_nb += 2 : face_nb++;
    }
    if (!vertex_nb || !face_nb)
    {
        printf("\033[0;33m✖ \033[0;31mObject file must contain at least vertices and faces\n\033[0;37m");
        exit(1);
    }
    scop->face_nb = face_nb;
    scop->normal_nb = normal_nb;
    scop->vertex_nb = vertex_nb;
    scop->texture_nb = texture_nb;
    fclose(file);
}

void load_file_obj(char *filename, t_scop *scop)
{
    file_obj_size(filename, scop);
    FILE *file;
    t_vertex *vertex;
    t_normal *normal;
    t_texture *texture;
    t_face *face;

    t_material *materials = NULL;
    char texture_name[32] = "";
    int texture_index = 0;

    int vertex_i = 0;
    int normal_i = 0;
    int texture_i = 0;
    int face_i = 0;
    short int checkVn = 0;
    short int checkVt = 0;
    if (!(vertex = (t_vertex *)malloc(sizeof(t_vertex) * scop->vertex_nb)))
        exit(1);
    if (!(normal = (t_normal *)malloc(sizeof(t_normal) * scop->normal_nb)))
        exit(1);
    if (!(texture = (t_texture *)malloc(sizeof(t_texture) * scop->texture_nb)))
        exit(1);
    if (!(face = (t_face *)malloc(sizeof(t_face) * scop->face_nb)))
        exit(1);

    if (!(file = fopen(filename, "r")))
        exit(1);

    char line[1024];
    while (fgets(line, 1024, file))
    {
        if (strncmp(line, "mtllib ", 7) == 0)
        {
            char mtl_name[64];
            char *path;
            if (!(path = sort_path(filename)))
                exit(1);
            sscanf(line, "mtllib %63s", mtl_name);
            if (!(materials = load_file_mtl(mtl_name, scop, path)))
                exit(1);
            free(path);
        }

        if (strncmp(line, "v ", 2) == 0)
        {
            if (checkVn || checkVt)
            {
                checkVn = 0;
                checkVt = 0;
            }
            if (sscanf(line, "v %f %f %f", &vertex[vertex_i].v.x, &vertex[vertex_i].v.y, &vertex[vertex_i].v.z) != 3)
            {
                printf("Invalid vertex\n");
                exit(1);
            }
            vertex_i++;
        }

        if (strncmp(line, "vt ", 3) == 0)
        {
            if (sscanf(line, "vt %f %f", &texture[texture_i].v.x, &texture[texture_i].v.y) != 2)
            {
                printf("Invalid texture coordonate\n");
                exit(1);
            }
            texture_i++;
            checkVt = 1;
        }

        if (strncmp(line, "vn ", 3) == 0)
        {

            if (sscanf(line, "vn %f %f %f", &normal[normal_i].v.x, &normal[normal_i].v.y, &normal[normal_i].v.z) != 3)
            {
                printf("Invalid normal\n");
                exit(1);
            }
            normal_i++;
            checkVt = 1;
            checkVn = 1;
        }
        if (strncmp(line, "usemtl", 6) == 0)
        {
            sscanf(line, "usemtl %31s", &texture_name[0]);
            texture_index++;
        }
        if (strncmp(line, "f ", 2) == 0)
        {
            if (count_char_in_string(line, ' ') >= 4)
            {
                if (checkVt && checkVn)
                {
                    if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0], &face[face_i].normal_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1], &face[face_i].normal_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2], &face[face_i].normal_indices[2],
                               &face[face_i].vertex_indices[3], &face[face_i].texture_indices[3], &face[face_i].normal_indices[3]) != 12)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face[face_i].n_face = 4;
                }
                else if (checkVt)
                {
                    if (sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2],
                               &face[face_i].vertex_indices[3], &face[face_i].texture_indices[3]) != 8)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face[face_i].n_face = 4;
                }
                else if (checkVn)
                {
                    if (sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].normal_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].normal_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].normal_indices[2],
                               &face[face_i].vertex_indices[3], &face[face_i].normal_indices[3]) != 8)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face[face_i].n_face = 4;
                }
                else
                {
                    if (sscanf(line, "f %d %d %d %d",
                               &face[face_i].vertex_indices[0],
                               &face[face_i].vertex_indices[1],
                               &face[face_i].vertex_indices[2],
                               &face[face_i].vertex_indices[3]) != 4)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face[face_i].n_face = 4;
                }

                if (scop->vertex_nb)
                {
                    face[face_i + 1].vertex_indices[0] = face[face_i].vertex_indices[2];
                    face[face_i + 1].vertex_indices[1] = face[face_i].vertex_indices[3];
                    face[face_i + 1].vertex_indices[2] = face[face_i].vertex_indices[0];
                }

                if (scop->texture_nb)
                {
                    face[face_i + 1].texture_indices[0] = face[face_i].texture_indices[2];
                    face[face_i + 1].texture_indices[1] = face[face_i].texture_indices[3];
                    face[face_i + 1].texture_indices[2] = face[face_i].texture_indices[0];
                }

                if (scop->normal_nb)
                {
                    face[face_i + 1].normal_indices[0] = face[face_i].normal_indices[2];
                    face[face_i + 1].normal_indices[1] = face[face_i].normal_indices[3];
                    face[face_i + 1].normal_indices[2] = face[face_i].normal_indices[0];
                }
                face[face_i].texture_index = texture_index;
                strcpy(face[face_i].texture_name, texture_name);
                face_i++;
            }
            else
            {
                if (checkVt && checkVn)
                {
                    if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0], &face[face_i].normal_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1], &face[face_i].normal_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2], &face[face_i].normal_indices[2]) != 9)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face->n_face = 3;
                }
                else if (checkVt)
                {
                    if (sscanf(line, "f %d/%d %d/%d %d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2]) != 6)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face->n_face = 3;
                }
                else if (checkVn)
                {
                    if (sscanf(line, "f %d/%d %d/%d %d/%d",
                               &face[face_i].vertex_indices[0], &face[face_i].normal_indices[0],
                               &face[face_i].vertex_indices[1], &face[face_i].normal_indices[1],
                               &face[face_i].vertex_indices[2], &face[face_i].normal_indices[2]) != 6)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face->n_face = 3;
                }
                else if (count_char_in_string(line, '/') == 0)
                {
                    if (sscanf(line, "f %d %d %d",
                               &face[face_i].vertex_indices[0],
                               &face[face_i].vertex_indices[1],
                               &face[face_i].vertex_indices[2]) != 3)
                    {
                        printf("Invalid face\n");
                        exit(1);
                    }
                    face->n_face = 3;
                }
                else
                {
                    exit(1);
                }
            }
            face[face_i].texture_index = texture_index;
            strcpy(face[face_i].texture_name, texture_name);
            face_i++;
        }
    }
    printf("%s", "\033[0;33m✓ \033[0;32mREAD DONE\n\033[0;37m");
    scop->vertices = vertex;
    scop->normal = normal;
    scop->texture = texture;

    set_color(&scop, face, materials);
    set_color_per_face(&scop);
    free(materials);
    if (!(scop->object = list_face_to_vertex(face, scop)))
    {
        printf("error obj\n");
        exit(1);
    }
    free(vertex);
    free(face);
    free(normal);
    free(texture);
    fclose(file);
}