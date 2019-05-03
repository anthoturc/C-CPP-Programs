#include "fs-util.h"
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>
#include <ufs/ufs/dir.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int
chkname(char *fname)
{
  /*
   * fname - the name of the file to check
   *
   * Given the fname of a file, check if it is a file that
   * would cause infinite recursion
   *
   * This includes the following directories:
   *  '.', '..'
   **/
  int this = strcmp(".", fname) == 0;
  int parent = strcmp("..", fname) == 0;
  return this || parent;
}


struct ufs2_dinode *
getnode(ino_t ino, struct fs *spr, char *part)
{
  /*
   * Given the inode number find the base address of the inode
   * and add the offset of the inode within the list of inodes
   **/
  unsigned int base = ino_to_fsba(spr, ino)*MINBSIZE;
  unsigned int addr = base + sizeof(struct ufs2_dinode)*ino_to_fsbo(spr, ino);
  struct ufs2_dinode *node = (struct ufs2_dinode *)(part + addr);
  return node;
}

void
print_file(struct ufs2_dinode *node, char *part)
{
  char *s = (char *)(part + node->di_db[0]*MINBSIZE);
  printf("%s\n", s);
}


void
dfs(struct ufs2_dinode *root, struct fs *spr, char *part, int padding, struct FIND *f)
{
  for (int blk = 0; blk < UFS_NDADDR && root->di_db[blk] != 0; ++blk) {
    /* 
     * off is used to keep track of where the next direct is in the datablock  
     * for this root node. After going through a direct, off is incremented by
     * the size of that direct. This is because not all directs are the same size
     **/
    int off = 0;
    while (off < root->di_size) {
      /* the list of directs located via the di_db arr */
      struct direct *curr = (struct direct *)(
        part + (root->di_db[blk]*MINBSIZE) + off
      );
      if (f != NULL) { /* searchiing for a file (cat) */
        int i = f->idx;
        if (strcmp(curr->d_name, f->comps[i]) == 0) { /* This is along the path*/
          struct ufs2_dinode *child = getnode(curr->d_ino, spr, part);
          if (curr->d_type == DT_REG && i == f->depth-1) { /* we are at the level of the file */
            print_file(child, part);
            return; /* sucessfully found the file */
          } else if (i > f->depth-1) { /* could not find file so stop */
            printf("FILE NOT FOUND\n");
            return;
          }

          if (curr->d_type == DT_DIR) { /* Only recurse on directories */
            f->idx += 1; /* searching in the next level */
            dfs(child, spr, part, 0, f);
          }
        }  
      } else { /* printing all contents of fs (find) */
        if (chkname(curr->d_name) || curr->d_namlen == 0) {
          /* '.', '..', or no name so do not include */
        } else {
          /* 
           * Used to generate the tabs required for expressing the hiearchy 
           * %*s%s specifies how much left padding to put on the name of the 
           * file/directory
           **/
          printf("%*s%s\n", padding, "", curr->d_name);
        
          if (curr->d_type == DT_DIR) { /* Only recurse on directories */
            struct ufs2_dinode *child = getnode(curr->d_ino, spr, part);
            dfs(child, spr, part, padding+1, NULL); /* padding for next level increases by 1 */
          }
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

