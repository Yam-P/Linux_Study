/**
*	@file		dopen.c
*	@manual		input file name using cmd arg
*				show the type of files in current directory.
*	@brief		use dir entry to know atributes about directory
*   @reference  :!man 3 readdir
*	@functions	opendir, closedir
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#define TYPE2STR(X) \
	((X) == DT_BLK      ? "This is a block device. " :\
	 (X) == DT_CHR      ? "This is a character device. " :\
	 (X) == DT_DIR      ? "This is a directory. " :\
	 (X) == DT_FIFO     ? "This is a named pipe (FIFO). " :\
	 (X) == DT_LNK      ? "This is a symbolic link. " :\
	 (X) == DT_REG      ? "This is a regular file. " :\
	 (X) == DT_SOCK     ? "This is a UNIX domain socket. " :\
	 (X) == DT_UNKNOWN  ? "The file type could not be determined. " :\
	"unkown")

int main(int argc, char **argv) {
	DIR *dp;
	// use "directory entry"
	struct dirent *entry;
	
	if(!(dp = opendir("."))) {
		printf("opendir() fail.\n");
		return -1;
	}

	// file name, type 출력
	while((entry = readdir(dp))) {
		printf("file name: %-15s, type: %s\n", 
				entry->d_name, TYPE2STR(entry->d_type));	
	}

	closedir(dp);

	return 0;
}
