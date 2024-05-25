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

  zip_int64_t indexcount = zip_get_num_entries(archive, ZIP_FL_UNCHANGED);
  for(int c = 0; c < indexcount; c++){
    int rc = 0;
    char buff[64];
    /* open file at index c */
    zip_file_t *zfile = zip_fopen_index(archive, c, ZIP_FL_UNCHANGED);
    if(zfile == NULL){
      fprintf(stderr, "unable to open file at index: %i\n", c);
      break;
    }
    FILE *out = fopen(zip_get_name(archive, c, ZIP_FL_UNCHANGED), "w");
    do {
      rc = zip_fread(zfile, buff, sizeof(buff));
      fputs(buff, out);
    }while(rc != 0);
    fclose(out);
    zip_fclose(zfile);
    
  }
  zip_close(archive);
  return EXIT_SUCCESS;
}
