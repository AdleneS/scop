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

t_shader read_path()
{
    const char *path = "./util/";
	DIR			*dir;
	t_dirent	*rd;
	t_shader shader;

	if (!(dir = opendir(path)))
		exit(1);
	while ((rd = readdir(dir)))
	{
		if (strncmp(rd->d_name, ".", 1) != 0 && strncmp(rd->d_name, "..", 2) != 0)
		{
			char *_path = NULL;
			if (!(_path = join(path, rd->d_name)))
				exit(1);

			if (strncmp(rd->d_name, "vertex_light.SHADER", 19) == 0) {
				printf("=> 1\n");
				if (!(shader.vertexShaderLight = sort_file_shader(_path)))
					exit(1);
			}

			if (strncmp(rd->d_name, "fragment_light.SHADER", 21) == 0) {
				printf("=> 2\n");
				if (!(shader.fragmentShaderLight = sort_file_shader(_path)))
					exit(1);
			}

			if (strncmp(rd->d_name, "vertex_source.SHADER", 20) == 0) {
				printf("=> 3\n");
				if (!(shader.vertexShaderSource = sort_file_shader(_path)))
					exit(1);
			}

			if (strncmp(rd->d_name, "fragment_source.SHADER", 22) == 0) {
				printf("=> 4\n");
				if (!(shader.fragmentShaderSource = sort_file_shader(_path)))
					exit(1);
			} 

			printf("%s\n", rd->d_name);
			free(_path);
		}
	}
	closedir(dir);
	return shader;
}