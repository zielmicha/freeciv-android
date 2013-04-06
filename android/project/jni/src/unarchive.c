#include "unarchive.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// WARNING: this library assumes that archive is trusted
// FIXME: don't assume little endian

static char* read_str(SDL_RWops* archive, int* msize);
static int64_t get_or_set_serial(const char* base, int64_t expected);
static void rmtree(const char* filename);

void unarchive(SDL_RWops* archive, const char* base) {
  uint64_t serial;
  SDL_RWread(archive, &serial, 8, 1);
  if(get_or_set_serial(base, serial)) {
    fprintf(stderr, "not extracting serial == %lld\n", serial);
    return;
  }
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

static void rmtree(const char* filename) {
  // filename shouldn't contain ', but check won't hurt
  const char* it;
  for(it=filename; *it != 0; it++)
    if(*it == '\'') abort();
  char* cmd = malloc(strlen(filename) + 100);
  sprintf(cmd, "rm -r '%s'", filename);
  system(cmd);
  free(cmd);
}

static int64_t get_or_set_serial(const char* base, int64_t expected) {
  const char* fn = "/_serial";
  char* path = malloc(strlen(base) + strlen(fn) + 2);
  strcpy(path, base);
  strcat(path, fn);
  FILE* f = fopen(path, "r");
  int64_t serial = -1;
  if(f != NULL) {
    fread(&serial, 8, 1, f);
    fclose(f);
  }
  if(serial == expected) {
    free(path);
    return 1;
  }
  rmtree(base);
  mkdir(base, 0700);
  f = fopen(path, "w");
  if(f == NULL) {
    perror("writing serial failed");
    fprintf(stderr, "serial file: %s\n", path);
    abort();
  }
  fwrite(&expected, 8, 1, f);
  fclose(f);
  free(path);
  return 0;
}

static char* read_str(SDL_RWops* archive, int* msize) {
  uint32_t size;
  SDL_RWread(archive, &size, 4, 1);
  char* buff = malloc(size + 1);
  SDL_RWread(archive, buff, 1, size);
  buff[size] = 0;
  if(msize != NULL) *msize = size;
  return buff;
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
