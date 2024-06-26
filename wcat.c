/*
 * author	Matthew Markfort <matthew.markfort@my.metrostate.edu>
 * class	ICS 462-01 Operating Systems (Metro State University)
 * date		22 May 2024
 * due		15 Jun 2024
 *
 * Like cat(1), output the contents from file to stdout
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void dumpfile(const char *filename){
  size_t linelength = 0;
  ssize_t bytes = 0;
  char *line = NULL;
  FILE *in = fopen(filename, "r");
  if(in == NULL)
  {
    fprintf(stderr, "fopen() failed\n");
    return;
  }
  while((bytes = getline(&line, &linelength, in)) > 0)
    {
      fputs(line, stdout);
      fflush(stdout);
    }
  /* free the line buffer */
  free(line);
  fclose(in);
}
  

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s in.txt ...\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* cycle through each file argument and write each line to stdout */
	for(int i = 1; i < argc; i++)
	{
	  dumpfile(argv[i]);
	}
	return EXIT_SUCCESS;
}

