#!/usr/local/bin/bash

# initialize and clear file system, on the 
# /dev/ada1p1 file. -E is used to erase the
# content of the disk before makign the filesystem
# superblock is not erased! (NOTE: -E can fail if device
# does not support 
newfs -U /dev/ada1p1

mount /dev/ada1p1 /mnt/newdisk

cd /mnt/newdisk

mkdir dir1
mkdir dir1/dir1.1
echo "deep in dir1" > dir1/dir1.1/file2
mkdir dir1/dir1.2
mkdir dir1/dir1.3

mkdir dir2
mkdir dir2/dir2.1
mkdir dir2/dir2.2
mkdir dir2/dir2.3

mkdir dir3
mkdir dir3/dir3.1
mkdir dir3/dir3.2
mkdir dir3/dir3.3

echo "file1 data" > file1
echo "dead inside" > dead
echo "stop eating" > beef
echo "This is a massive file that will consist of many bytes.. For example, byte 1, 2, 3, 4, 5, 7 (notice that 6 was skipped), 8, 9, 10, 12 (did it again.. woo I am tired and would like to go home now. Oh wait I can't. Yay. You ever think about how you printf when you dont give an f? probably not. this file still isnt long enough to be considered a 'long' file. I bet if this was a png it would be a massive file. PNGs kind of suck because of that." >big-file

cd /home/antho/Desktop/CS414/Assignment2

umount /dev/ada1p1

dd if=/dev/ada1p1 of=partition.img

xxd partition.img > partition.hex
