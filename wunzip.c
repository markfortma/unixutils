/*
 * author    Matthew Markfort <matthew.markfort@my.metrostate.edu>
 * class     ICS 462-01 Operating Systems / Summer 2024 / Metro State University
 * date      22 May 2024
 * due       15 Jun 2024
 *
 * Extract files from a ZIP archive
 */

#include<stdio.h>
#include<stdlib.h>
#include<zip.h>

void usage(const char *progname){
  printf("Usage: %s in.zip\n", progname);
}

int main(int argc, char *argv[]){
  if(argc != 2){
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  int failcode;
  zip_t *archive = NULL;
  if((archive = zip_open(argv[1], ZIP_RDONLY, &failcode)) == NULL){
    fprintf(stderr, "failed to open: %s for reading\n", argv[1]);
    return EXIT_FAILURE;
  }

  zip_close(archive);
  return EXIT_SUCCESS;
}
