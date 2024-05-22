#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char **argv)
{
	int records = 0;
	size_t linelength = 0;
	ssize_t offset = 0, bytes = 0;
	char *line = NULL;
	FILE *in = NULL;
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s in.txt ...\n", argv[0]);
		return EXIT_FAILURE;
	}
	for(int i = 1; i < argc; i++)
	{
		in = fopen(argv[i], "r");
		while(!feof(in))
		{
			bytes = getline(&line, &linelength, in);
			if(bytes < 0)
			{
				break;
			}
			printf(line);
			offset += bytes;
		}
		free(line);
		fclose(in);
	}
	return EXIT_SUCCESS;
}
