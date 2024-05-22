/*
 * author    Matthew Markfort <matthew.markfort@my.metrostate.edu>
 * class     ICS 462-01 Operating Systems / Summer 2024 / Metro State University
 * date      22 May 2024
 * due       15 Jun 2024
 *
 * Create a ZIP archive given the supplied files
 */

#include<stdio.h>
#include<stdlib.h>
#include<zip.h>

void usage(const char *progname){
  fprintf(stderr, "Usage: %s destination.zip file1 file2 ...\n", progname);
}

int main(int argc, char *argv[]){
  if(argc < 2){
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  zip_t *archive = NULL;
  if((archive = zip_open(argv[1], ZIP_CREATE | ZIP_TRUNCATE)) == NULL){
    fprintf(stderr, "failed to open/create ZIP archive\n");
    return EXIT_FAILURE;
  }

  
  return EXIT_SUCCESS;
}
