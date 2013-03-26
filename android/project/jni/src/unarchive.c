#include "unarchive.h"
#include <stdio.h>
#include <stdint.h>
// WARNING: this library assumes that archive is trusted
// FIXME: don't assume little endian

char* read_str(SDL_RWops* archive, int* msize) {
  uint32_t size;
  SDL_RWread(archive, &size, 4, 1);
  char* buff = malloc(size + 1);
  SDL_RWread(archive, buff, 1, size);
  buff[size] = 0;
  if(msize != NULL) *msize = size;
  return buff;
}

void unarchive(SDL_RWops* archive, const char* base) {
  uint32_t count;
  SDL_RWread(archive, &count, 4, 1);
  while(count --) {
    uint32_t type;
    SDL_RWread(archive, &type, 4, 1);
    char* name = read_str(archive, NULL);
    int content_size;
    char* content = read_str(archive, &content_size);
    char* path = malloc(strlen(base) + strlen(name) + 3);
    strcpy(path, base);
    strcat(path, "/");
    strcat(path, name);
    fprintf(stderr, "extracting %s\n", path);
    if(type == 1) {
      if(mkdir(path, 0700) < 0) {
        perror("mkdir");
      }
    } else {
      FILE* f = fopen(path, "w");
      if(f == NULL) {
        perror("fopen");
      } else {
        fwrite(content, content_size, 1, f);
        fclose(f);
      }
    }
    free(name);
    free(content);
  }
}

#ifdef MAIN
int main(int argc, char** argv) {
  if(argc != 3) {
    fprintf(stderr, "Usage: unarchive archive dest\n");
    exit(1);
  }
  SDL_RWops* ops = SDL_RWFromFile(argv[1], "rb");
  unarchive(ops, argv[2]);
}
#endif
