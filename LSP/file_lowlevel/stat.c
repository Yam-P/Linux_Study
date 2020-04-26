#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	// file의 static 정보를 담고 있는 구조체. 
	struct stat statBuf;

	if (argc < 2 ) {
		printf("usage: Enter the file name as a variable\n");
	}

	if (stat(argv[1], &statBuf)) {
		printf("stat() fail\n");
		return -1;
	}
	
	printf("file name: %s\n", argv[1]);
	printf("file size: %ld\n", statBuf.st_size);
	
	// mode check
	if (S_ISDIR(statBuf.st_mode)) {
		printf("it is directory.\n");
	}
	else if (S_ISREG(statBuf.st_mode)) {
		printf("it is regular file.\n");
	}
	else {
		printf("???\n");
	}


	return 0;
}
