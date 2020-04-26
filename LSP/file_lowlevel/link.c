/**
*	@file		link.c
*	@manual		input file name using cmd arg
*	@brief		make general file, hard/symbolic link files	
*	@functions	link, symlink 
*
*	@author		yamp
*	@date		Apr 27, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int file_open(char *target) {
	FILE *fp;
	if (!(fp = fopen(target, "w"))) {
		return -1;
	}
	fprintf(fp, "Hello world!\n");

	fclose(fp);
	return 0;
}

char *getTitle(char *target, char *ref) {
	char *ret = malloc(sizeof(char) * 30);
	strcpy(ret, target);
	strcat(ret, ref);

	return ret;
}

int main(int argc, char **argv) {
	char *target = argv[1];
	char *targetHl = getTitle(target, ".hl");
	char *targetSl = getTitle(target, ".sl");

	if(file_open(target)) {
		printf("fopen() fail.\n");
		return -1;
	}
	printf("fopen() success.\n");

	if (link(target, targetHl)) {
		printf("link() fail.\n");
		return -1;
	}
	printf("hard link success. file name: %s\n", targetHl);
	
	if (symlink(target, targetSl)) {
		printf("symlink() fail.\n");
		return -1;
	}
	printf("symbolic link success. file name: %s\n", targetSl);

	return 0;
}
