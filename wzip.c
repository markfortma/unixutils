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
#include<sys/stat.h>
#include<zip.h>

void usage(const char *progname){
  fprintf(stderr, "Usage: %s destination.zip file1 file2 ...\n", progname);
}

int main(int argc, char *argv[]){
  if(argc < 3){
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  int err;
  zip_t *archive = NULL;
  if((archive = zip_open(argv[1], ZIP_CREATE, &err)) == NULL){
    fprintf(stderr, "failed to open/create ZIP archive\n");
    return EXIT_FAILURE;
  }

  for(int i = 2; i < argc; i++){
    zip_uint64_t len;
    zip_source_t *zsrc;
    if((zsrc = zip_source_file(archive, argv[i], 0, ZIP_LENGTH_TO_END)) == NULL){
      fprintf(stderr, "failed to open source: %s\n", argv[i]);
      continue;
    }
    if((len = zip_file_add(archive, argv[i], zsrc, ZIP_FL_OVERWRITE)) < 0){
      fprintf(stderr, "failed to archive: %s\n", argv[i]);
      zip_source_free(zsrc);
      continue;
    }
  }
  
  zip_close(archive);
  return EXIT_SUCCESS;
}
