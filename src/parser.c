#include "scop.h"

void load_file_obj(char *filename, t_scop *scop)
{
    FILE *file;
    t_vertex *vertex_list = NULL;
    t_vertex *normal_list = NULL;
    t_texture *textur_list = NULL;
    t_face *face_list = NULL;

    int vertex_nb = 0;
    int texture_nb = 0;
    int normal_nb = 0;
    int face_nb = 0;
    short int checkVn = 0;
    short int checkVt = 0;
    if (!(file = fopen(filename, "r")))
        exit(1);

    char line[1024];

    while (fgets(line, 1024, file))
    {

        if (strncmp(line, "mtllib ", 7) == 0)
        {
            char mtl_name[1024];
            char *path = sort_path(filename);
            sscanf(line, "mtllib %s", mtl_name);
            load_file_mtl(mtl_name, scop, path);
        }

        if (strncmp(line, "v ", 2) == 0)
        {
            if (checkVn || checkVt)
            {
                checkVn = 0;
                checkVt = 0;
            }
            t_vertex *vertex;
            if (!(vertex = malloc(sizeof(t_vertex))))
            {
                exit(1);
            }
            vertex->next = NULL;
            sscanf(line, "v %f %f %f", &vertex->v.x, &vertex->v.y, &vertex->v.z);
            vertex_nb++;
            list_pushback(&vertex_list, vertex);
        }

        if (strncmp(line, "vt ", 3) == 0)
        {
            t_texture *texture;
            if (!(texture = malloc(sizeof(t_texture))))
            {
                exit(1);
            }
            texture->next = NULL;
            sscanf(line, "vt %f %f", &texture->v.x, &texture->v.y);
            texture_nb++;
            list_pushback_tex(&textur_list, texture);
            checkVt = 1;
        }

        if (strncmp(line, "vn ", 3) == 0)
        {
            t_vertex *normal;
            if (!(normal = malloc(sizeof(t_vertex))))
            {
                exit(1);
            }
            normal->next = NULL;
            sscanf(line, "vn %f %f %f", &normal->v.x, &normal->v.y, &normal->v.z);
            normal_nb++;
            list_pushback(&normal_list, normal);
            checkVt = 1;
            checkVn = 1;
        }

        if (strncmp(line, "f ", 2) == 0)
        {
            t_face *face;
            if (!(face = malloc(sizeof(t_face))))
            {
                exit(1);
            }
            face->next = NULL;

            if (count_char_in_string(line, ' ') >= 4)
            {
                if (checkVt && checkVn)
                {
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2],
                           &face->vertex_indices[3], &face->texture_indices[3], &face->normal_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else if (checkVt)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2],
                           &face->vertex_indices[3], &face->texture_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else if (checkVn)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->normal_indices[2],
                           &face->vertex_indices[3], &face->normal_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                else
                {
                    sscanf(line, "f %d %d %d %d",
                           &face->vertex_indices[0],
                           &face->vertex_indices[1],
                           &face->vertex_indices[2],
                           &face->vertex_indices[3]);
                    face->n_face = 4;
                    face_nb++;
                }
                
            }
            else
            {
                if (checkVt && checkVn)
                {
                    sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2], &face->normal_indices[2]);
                    face->n_face = 3;
                }
                else if (checkVt)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->texture_indices[0],
                           &face->vertex_indices[1], &face->texture_indices[1],
                           &face->vertex_indices[2], &face->texture_indices[2]);
                    face->n_face = 3;
                }
                else if (checkVn)
                {
                    sscanf(line, "f %d/%d %d/%d %d/%d",
                           &face->vertex_indices[0], &face->normal_indices[0],
                           &face->vertex_indices[1], &face->normal_indices[1],
                           &face->vertex_indices[2], &face->normal_indices[2]);
                    face->n_face = 3;
                }
                else
                {
                    sscanf(line, "f %d %d %d",
                           &face->vertex_indices[0],
                           &face->vertex_indices[1],
                           &face->vertex_indices[2]);
                    face->n_face = 3;
                }
            }
            face_nb++;
            list_pushback_face(&face_list, face);
        }
    }

    scop->size = vertex_nb;
    scop->textur_nb = texture_nb;
    scop->normal_nb = normal_nb;
    scop->face_nb = face_nb;
    list_to_array(scop, vertex_list);
    list_to_array_texture(scop, textur_list);
    list_to_array_normal(scop, normal_list);
    list_to_array_face(scop, face_list);

    if(!(scop->object = list_face_to_vertex(face_list, scop))) {
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
    fclose(file);
}
