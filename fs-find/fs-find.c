#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/dir.h>
#include <ufs/ufs/dinode.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fs-util.h"

int 
main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: ./fs-find <filesystem.img>\n");
    return 1;
  }

  int fd;
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    perror("fs-find: open in main @ line 104\n");
    return 1;
  }
  
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fs-find: fstat in main @ line 110\n");
    return 1;
  }


  char *part; /* Holds the partition */
  if ((part = (char *)mmap(
      NULL,
      sb.st_size, /* Read entire partition img */
      PROT_READ,
      MAP_PRIVATE,
      fd,
      0)) == MAP_FAILED) {
    perror("fs-find: mmap in main @ line 117\n");
    return 1;
  }

  /* Superblock lies at offset SBLOCK_UFS2 */
  struct fs *spr = (struct fs *)(part + SBLOCK_UFS2);

  /* Access the root inode in the partition */
  struct ufs2_dinode *root = getnode(UFS_ROOTINO, spr, part);

  /* Run a Depth First Search on the fs tree from the root */
  dfs(root, spr, part, 0, NULL);
  
  if (close(fd) == -1) {
    perror("fs-find: close in main @ line 136\n");
    return 1;
  }

  if (munmap((void *)part, sb.st_size) == -1) {
    perror("fs-find: mmap in main @ line 142\n");
    return 1;
  }
  return 0;
} 

