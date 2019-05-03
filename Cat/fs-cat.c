#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
#include <unistd.h>
#include <fcntl.h>

#include "fs-util.h"

#define DELIM "/"
#define NUMARGS 3

int
main(int argc, char **argv)
{
  if (argc != NUMARGS) {
    perror("Usage: ./fs-cat <filesystem.img> <path/to/file>\n");
    return 1;
  }

  int fd;
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    perror("fs-cat: open in main @ line 26\n");
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fs-cat: fstat in main @ line 31\n");
    return 1;
  }

  char *part;
  if ((part = (char *)mmap(
          NULL,
          sb.st_size,
          PROT_READ,
          MAP_PRIVATE,
          fd,
          0)) == MAP_FAILED) {
    perror("fs-cat: mmap in main @ line 38\n");
    return 1;
  }

  /* Super block lies at an offste of SBLOCK_UFS2 */
  struct fs *spr = (struct fs *)(part + SBLOCK_UFS2);

  /* access root node */
  struct ufs2_dinode *root = getnode(UFS_ROOTINO, spr, part);

  /* split the path/to/file into a list of directories and a file */
  char *path = argv[2];
  
  int len = 0;
  int ncomps = 0;
  /* count number of '/'s in path */
  for (int i = 0; path[i] != '\0'; ++i) {
    if (path[i] == '/') {
      ++ncomps;
    }
    ++len;
  }

  char oldpath[len+1];
  strncpy(oldpath, argv[2], len);
  oldpath[len+1] = '\0';

  char *path_comps[ncomps+1]; /* path components, for n slashes there are n+1 names */
  int i = 0;
  path_comps[i] = strtok(path, DELIM); 
  while (path_comps[i] != NULL) {
    path_comps[++i] = strtok(NULL, DELIM);
  }

  struct FIND *f;
  if ((f = (struct FIND *)malloc(sizeof(struct FIND))) == NULL) {
    perror("fs-cat: malloc in main @ line 80\n");
    return 1;
  }
  f->depth = ncomps+1;
  f->idx = 0; /* start from the top level */
  f->comps = path_comps;
  f->path = oldpath;
  /* perform depth first search from root to file */
  dfs(root, spr, part, 0, f);

  free(f);
  if (close(fd) == -1) {
    perror("fs-cat: close in main @ line 92\n");
    return 1;
  }

  if (munmap((void *)part, sb.st_size) == -1) {
    perror("fs-cat: munmap in main @ line 97\n");
    return 1;
  }
  return 0;
}

