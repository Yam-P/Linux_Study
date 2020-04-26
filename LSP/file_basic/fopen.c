/**
*	@file		fopen.c
*	@manual		input file name using cmd arg
*	@brief		way to open file using file pointer, FILE *fp
*	@functions	fopen, fclose, fputs, fgets
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <string.h>

int write_to_file(const char *target) {
	FILE *fp;

	fp = fopen(target, "w");
	if (fp == NULL) {
		perror("fopen error\n");
		return -1;
	}

	fputs("hello world!", fp);
	fclose(fp);

	return 0;
}

int read_from_file(const char *target) {
	FILE *fp;
	char buf[1024];

	fp = fopen(target, "r");
	if (fp == NULL) {
		perror("fopen error\n");
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	fgets(buf, sizeof(buf), fp);
	fclose(fp);

	printf("%s\n", buf);

	return 0;

}


int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: Enter the document file name as an argument.\n");
		return -1;
	}

	char *target = argv[1];
	printf("open '%s' file using fopen.\n\n", target);
	// file 수행시 내용 입력
	if (write_to_file(target)) {
		perror("write_to_file() fail.\n");
		return -1;
	}
	printf("write_to_file() success.\n");

	// file 수행시 내용 출력
	if (read_from_file(target)) {
		perror("read_from_file fail.\n");
		return -1;
	}
	printf("read_from_file() success.\n");

	return 0;
}
