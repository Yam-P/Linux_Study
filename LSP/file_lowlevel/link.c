#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TARGET_FILE "doc_link.txt"
int file_open(void) {
	FILE *fp;
	if (!(fp = fopen(TARGET_FILE, "w"))) {
		return -1;
	}
	fprintf(fp, "Hello world!\n");

	fclose(fp);
	return 0;
}

int main(int argc, char **argv) {
	if(file_open()) {
		printf("fopen() fail.\n");
		return -1;
	}
	printf("fopen() success.\n");

	if (link(TARGET_FILE, "doc_link.hl")) {
		printf("link() fail.\n");
		return -1;
	}
	printf("hard link success.\n");
	
	if (symlink(TARGET_FILE, "doc_link.sl")) {
		printf("symlink() fail.\n");
		return -1;
	}
	printf("symbolic link success.\n");

	return 0;
}
