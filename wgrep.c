/*
 * author    Matthew Markfort <matthew.markfort@my.metrostate.edu>
 * class     ICS 462-01 Operating Systems / Summer 2024 / Metro State University
 * date      22 May 2024
 * due       15 Jun 2024
 *
 * Find the provided string in supplied files
 * Comparable to grep(1)
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pcre.h>

#define CAPTUREVECTORSIZE 60

void usage(const char *progname){
  printf("Usage: %s Regexp file1 file2 ...\n", progname);
}

int match_in_file(const char *path, pcre *regexp){
  char *line = NULL;
  int lineno = 0;
  size_t linelen = 0;
  ssize_t nbytes = 0;
  FILE *in = NULL;

  int rc;
  int capturegroups[CAPTUREVECTORSIZE];
  /* open file for reading*/
  in = fopen(path, "r");
  while(!feof(in)){
    /* read a line from in */
    nbytes = getline(&line, &linelen, in);
    /* if 0 bytes were read, at end of file - exit while */
    if(0 == nbytes) break;

    rc = pcre_exec(
		   regexp,        // compile regex
		   NULL,          // optional results from pcre_study
		   line,          // input string
		   (int) strlen(line), // input string length
		   0,             // start of string offset
		   0,             // PCRE flags
		   capturegroups,
		   CAPTUREVECTORSIZE);
    // handle errors from pcre_exec
    if(0 < rc)
      // act like 'grep -n'
      printf("%i:%s\n", lineno, line);
    lineno++;
  }
  /* free the buffer containing line */
  if(line != NULL) free(line);
  fclose(in);
}

int main(int argc, char *argv[]){
  if(argc < 3){
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  int errcode = 0;
  const char *errmsg = NULL;
  pcre *regexp = pcre_compile(argv[1], // RegExp pattern
			      0,       // flags
			      &errmsg, // error message
			      &errcode,// error code
			      NULL);   // use default locale
  if(regexp == NULL){
    fprintf(stderr, "failed to compile RegExp: %d: %s\n", errcode, errmsg);
    return EXIT_FAILURE;
  }

  /* cycle through files and output their matching lines */
  for(int i = 2; i < argc; i++)
    match_in_file(argv[i], regexp);
  /* free the regexp pattern */
  pcre_free(regexp);
  return EXIT_SUCCESS;
}
