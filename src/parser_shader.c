#include "scop.h"

char *sort_file_shader(char *_path)
{
	char *buffer = NULL;
	long length;
	FILE * f = fopen(_path, "r");

	if (f)
	{
  		fseek(f, 0, SEEK_END);
  		length = ftell(f);
  		fseek(f, 0, SEEK_SET);
  		if (!(buffer = (char *)malloc(length)))
		  	return NULL;
    		fread(buffer, 1, length, f);
  		fclose(f);
	}
	return strdup(buffer);
}

t_shader *read_path()
{
    const char *path = "./util/";
	DIR			*dir;
	t_dirent	*rd;
	t_shader *shader_list = NULL;

	if (!(dir = opendir(path)))
		return NULL;
	while ((rd = readdir(dir)))
	{
		if (strncmp(rd->d_name, ".", 1) != 0 && strncmp(rd->d_name, "..", 2) != 0)
		{
			t_shader *new = new;
			if (!(new = (t_shader *)malloc(sizeof(t_shader))))
				return NULL;
			char *_path = NULL;
			if (!(_path = join(path, rd->d_name)))
				return NULL;
			new->name = strdup(rd->d_name);
			if (!(new->shader = sort_file_shader(_path)))
				return NULL;
			list_pushback_shader(&shader_list, new);
		}
	}
	closedir(dir);
	return shader_list;
}