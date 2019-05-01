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


int
chkname(char *fname)
{
  /*
   * fname - the name of the file to check
   *
   * Given the fname of a file, check if it is a file that
   * is not represented in the di_nlink(s) of the corresponding
   * ufs2_dinode. 
   *
   * This include the following directories:
   *  '.', '..', '.snap'
   **/
  int this = strcmp(".", fname) == 0;
  int parent = strcmp("..", fname) == 0;
  return this || parent;
}

char *
mkpadding(int padding) {
  /* 
   * tabs - the number of tabs to returns in the string
   *
   * Given tabs, return a string of length tabs that will 
   * contain ' ' characters repeated padding number of times.
   **/
  char *pad;
  
  if((pad = (char *)malloc(sizeof(padding))) == NULL) {
    perror("fs-find: malloc in mktabs @ line 44\n");
  }
  
  for (int i = 0; i < padding; ++i) {
    *(pad+i) = ' ';
  }

  return pad;
}

struct ufs2_dinode *
getnode(ino_t ino, struct fs *spr, char *part)
{
  /* 
   * ino  - the inode number
   * spr  - the superblock
   * part - the partition
   *
   * Given the indode number find the base address of the inode
   * and add the offset of the inode within the list of inodes
   * */
  unsigned int base = ino_to_fsba(spr, ino)*MINBSIZE;
  unsigned int addr = base + sizeof(struct ufs2_dinode)*ino_to_fsbo(spr, ino);
  struct ufs2_dinode *node = (struct ufs2_dinode *)(part + addr);

  return node;
}

void
dfs(struct ufs2_dinode *root, struct fs *spr, char *part, int padding)
{
  /*
   * root - pointer to the inode that will be searched for information
   * spr  - pointer to the super block
   * part - pointer to the partition
   * padding - spacing to place to left of file so that fname is printed
   **/

  /* 
   * off is used to keep track of where the next direct is in the datablock  
   * for this root node. After going through a direct, off is incremented by
   * the size of that direct. This is because not all directs are the same size
   **/
  int off = 0;
  for (int blk = 0; blk < UFS_NDADDR; ++blk) {
      
    for (int i = 0; i < root->di_nlink; ++i) {
      /* the current directory is located via the di_db arr */
      struct direct *curr = (struct direct *)(
          part + (root->di_db[i]*MINBSIZE) + off
      );
      if (chkname(curr->d_name)) { /* '.', '..', so do not include */
        --i;
      } else if (curr->d_namlen == 0) { /* no information in direct */
        continue;
      } else {
        /* Used to generate the tabs required for expressing the hiearchy */
        char *t = "";
        if (padding != 0) {
          t = mkpadding(padding);
        }
        
        printf("%s%s\n", t, curr->d_name);
        
        if (padding != 0) {
          free(t);
        }

        if (curr->d_type == DT_DIR) { /* Only recurse on directories */
          /* Get the next inode pointed to by this direct */
          struct ufs2_dinode *child = getnode(curr->d_ino, spr, part);

          dfs(child, spr, part, padding+1); /* padding for next level increases by 1 */
        }
      }
      /* 
       * Since not all entires in direct are of the same length, the prev is offset
       * by d_reclen bytes in order
       **/
      off += curr->d_reclen;
    }
  }
}

int 
main(int argc, char **argv)
{
  if (argc != 2) {
    printf("Usage: ./fs-find <filesystem.img>\n");
    return 1;
  }

  int fd;
  if ((fd = open(argv[1], O_RDONLY)) == -1) {
    perror("fs-find: open in main @ line 139\n");
    return 1;
  }
  
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("fs-find: fstat in main @ line 144\n");
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
    perror("fs-find: mmap in main @ line 151\n");
    return 1;
  }

  /* Superblock lies at offset SBLOCK_UFS2 */
  struct fs *spr = (struct fs *)(part + SBLOCK_UFS2);

  /* Access the root inode in the partition */
  struct ufs2_dinode *root = getnode(UFS_ROOTINO, spr, part);

  /* Run a Depth First Search on the fs tree from the root */
  dfs(root, spr, part, 0);
  
  if (close(fd) == -1) {
    perror("fs-find: close in main @ line 172\n");
    return 1;
  }

  return 0;
} 
