/*
 *  fs-util.h
 *  
 *  This library declares functions that are used in 
 *  fs-cat.c and fs-find.c.
 */

#ifndef _FS_UTIL_H_
#define _FS_UTIL_H_

#include <sys/types.h>
#include <ufs/ufs/dinode.h>
#include <ufs/ffs/fs.h>

/*
 * chkname(...) returns 1 if fname is '.' or '..', and 0 otherwise
 *
 * fname - the string to check
 **/
int
chkname(char *fname);

/*
 * getnode(...) returns a pointer to the inode defined by ino
 * 
 * ino  - the inode number
 * spr  - pointer to the superblock
 * part - pointer to the beginning of the partition
 *
 **/
struct ufs2_dinode * getnode(ino_t ino, struct fs *spr, char *part);

/*
 * print_file(...) prints the contents of the pointed to by node
 *
 * node - the inode of the file
 * n    - the number of bytes in the file
 **/
void
print_file(struct ufs2_dinode *node, char *part);

/*
 * The FIND struct is used to store
 * information about the file that is or is not being
 * searched for in the file system.
 *
 * depth - the depth of the file to be searched for in the file system
 * comps - a list of strings obtained from splitting the path/to/file
 * on the '/' delimeter
 * idx - the level to start searching from, this will usually be zero
 **/
struct FIND {
  int depth;
  char **comps;
  int idx;
};

/*
 * dfs(...) performs a modified depth first search on the
 * file system defined by spr. There are two types of these searches
 * that can be achieved based on the value of f.
 * 
 * 1. f is NULL
 *
 * If f is NULL then all of the contents of the filesystem will be
 * printed. In other word, there is no specific file being searched for. 
 *
 * 2. f is not NULL
 *
 * If f is not NULL then there is a file to be searched for and that files
 * contents will be printed.
 *
 * root     - the root inode of the filesystem
 * spr      - the super block of the file system
 * part     - the partition
 * padding  - amount of padding to put at this level when printing name (find)
 * f        - the information related to the file being searched for (cat)
 *
 * NOTE: 
 * f will be NULL in the fs-find program
 * padding will be 0 in the fs-cat program
 **/
void
dfs(struct ufs2_dinode *root, struct fs *spr, char *part, int padding, struct FIND *f); 

#endif /* _FS_UTIL_H_ */

