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
    scop->face_nb = face_nb;
    scop->normal_nb = normal_nb;
    scop->vertex_nb = vertex_nb;
    scop->texture_nb = texture_nb;
    printf("v: %d | vt: %d | n: %d | f: %d\n", vertex_nb, texture_nb, normal_nb, face_nb);
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
    int process = 0;
    short int checkVn = 0;
    short int checkVt = 0;

    if (!(vertex = malloc(sizeof(t_vertex) * scop->vertex_nb)))
        exit(1);
    if (!(normal = malloc(sizeof(t_normal) * scop->normal_nb)))
        exit(1);
    if (!(texture = malloc(sizeof(t_texture) * scop->texture_nb)))
        exit(1);
    if (!(face = malloc(sizeof(t_face) * scop->face_nb)))
        exit(1);

    if (!(file = fopen(filename, "r")))
        exit(1);

    char line[1024];

    while (fgets(line, 1024, file))
    {
        process++;
        if (strncmp(line, "mtllib ", 7) == 0)
        {
            char mtl_name[64];
            char *path = sort_path(filename);
            sscanf(line, "mtllib %s", mtl_name);
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
            sscanf(line, "v %f %f %f", &vertex[vertex_i].v.x, &vertex[vertex_i].v.y, &vertex[vertex_i].v.z);
            vertex_i++;
        }

        if (strncmp(line, "vt ", 3) == 0)
        {
            sscanf(line, "vt %f %f", &texture[texture_i].v.x, &texture[texture_i].v.y);
            texture_i++;
            checkVt = 1;
        }

        if (strncmp(line, "vn ", 3) == 0)
        {
            sscanf(line, "vn %f %f %f", &normal[normal_i].v.x, &normal[normal_i].v.y, &normal[normal_i].v.z);
            normal_i++;
            checkVt = 1;
            checkVn = 1;
        }
        if (strncmp(line, "usemtl", 6) == 0)
        {
            sscanf(line, "usemtl %s", &texture_name[0]);
            texture_index++;
        }
        if (strncmp(line, "f ", 2) == 0)
        {
            if (count_char_in_string(line, ' ') >= 4)
            {
                if (checkVt && checkVn)
                {

                    //////////////////////////////PREVIENT LES SEGFAULTS DES OBJETS AVEC 4 VERTEX PAR FACE//////////////////////////////////
                    //exit(1);
                    //////////////////////////////PREVIENT LES SEGFAULTS DES OBJETS AVEC 4 VERTEX PAR FACE//////////////////////////////////
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0], &face[face_i].normal_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1], &face[face_i].normal_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2], &face[face_i].normal_indices[2],
                           &face[face_i].vertex_indices[3], &face[face_i].texture_indices[3], &face[face_i].normal_indices[3]);
                    face[face_i].n_face = 4;
                }
                else if (checkVt)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2],
                           &face[face_i].vertex_indices[3], &face[face_i].texture_indices[3]);
                    face[face_i].n_face = 4;
                }
                else if (checkVn)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].normal_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].normal_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].normal_indices[2],
                           &face[face_i].vertex_indices[3], &face[face_i].normal_indices[3]);
                    face[face_i].n_face = 4;
                }
                else
                {
                    sscanf(line, "f %d %d %d %d",
                           &face[face_i].vertex_indices[0],
                           &face[face_i].vertex_indices[1],
                           &face[face_i].vertex_indices[2],
                           &face[face_i].vertex_indices[3]);
                    face[face_i].n_face = 4;
                }

                face[face_i + 1].vertex_indices[0] = face[face_i].vertex_indices[2];
                face[face_i + 1].vertex_indices[1] = face[face_i].vertex_indices[3];
                face[face_i + 1].vertex_indices[2] = face[face_i].vertex_indices[0];

                face[face_i + 1].texture_indices[0] = face[face_i].texture_indices[2];
                face[face_i + 1].texture_indices[1] = face[face_i].texture_indices[3];
                face[face_i + 1].texture_indices[2] = face[face_i].texture_indices[0];

                face[face_i + 1].normal_indices[0] = face[face_i].normal_indices[2];
                face[face_i + 1].normal_indices[1] = face[face_i].normal_indices[3];
                face[face_i + 1].normal_indices[2] = face[face_i].normal_indices[0];
                face[face_i].texture_index = texture_index;
                strcat(face[face_i].texture_name, texture_name);
                face_i++;
            }
            else
            {
                if (checkVt && checkVn)
                {
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0], &face[face_i].normal_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1], &face[face_i].normal_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2], &face[face_i].normal_indices[2]);
                    face->n_face = 3;
                }
                else if (checkVt)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].texture_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].texture_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].texture_indices[2]);
                    face->n_face = 3;
                }
                else if (checkVn)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face[face_i].vertex_indices[0], &face[face_i].normal_indices[0],
                           &face[face_i].vertex_indices[1], &face[face_i].normal_indices[1],
                           &face[face_i].vertex_indices[2], &face[face_i].normal_indices[2]);
                    face->n_face = 3;
                }
                else
                {
                    sscanf(line, "f %d %d %d",
                           &face[face_i].vertex_indices[0],
                           &face[face_i].vertex_indices[1],
                           &face[face_i].vertex_indices[2]);
                    face->n_face = 3;
                }
            }
            face[face_i].texture_index = texture_index;
            strcat(face[face_i].texture_name, texture_name);
            face_i++;
        }
    }
    printf("%s", "\033[0;33m✓ \033[0;32mREAD DONE\n\033[0;37m");
    scop->vertices = vertex;
    scop->normal = normal;
    scop->texture = texture;

    set_color(&scop, face, materials);
    free(materials);
    if (!(scop->object = list_face_to_vertex(face, scop)))
    {
        printf("error obj\n");
        exit(1);
    }

    //print_vertex_face(scop->object, scop->face_nb * 3);

    //print_list_face_obj(scop);

    // print_array(scop->vertices, scop->size * 3);
    // print_array_vt(scop->texture, scop->textur_nb * 2);
    // print_array_vn(scop->normal, scop->normal_nb * 3);

    //print_array_face(scop->faces_v, scop->face_nb * 3);
    //print_array_face_vt(scop->faces_vt, scop->textur_nb * 2);
    //print_array_face(scop->faces_vn, scop->face_nb * 3);

    //print_list_v(vertex_list);
    //print_list_vt(textur_list);
    //print_list_vn(normal_list);
    //print_list_face(face_list);
    free(vertex);
    free(face);
    free(normal);
    free(texture);
    fclose(file);
}