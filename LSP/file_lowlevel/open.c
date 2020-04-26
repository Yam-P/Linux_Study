/**
*	@file		open.c
*	@manual		input file name using cmd arg
*	@brief		open file with O_ flag and assign permission with file descriptor
*	@functions  open, close, dprintf, 
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TARGET_FILE "doc_open.txt"
static int write_file(char *target) {
	int fd;
	
	// 파일이 존재하지 않는다면, 파일을 생성.
	fd = open(target, O_WRONLY | O_CREAT, 0644);
	if (fd == -1) {
		printf("open() create fail.\n");
		return -1;
	}

	dprintf(fd, "Write.. Hello World! %d\n", 123);
	close(fd);
	return 0;
}

static int trunc_file(char *target) {
	int fd;

	// 파일이 비어있지 않다면, 내용 덮어쓰기.
	fd = open(target, O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) {
		printf("open() trunc fail.\n");
		return -1;
	}
	
	dprintf(fd, "Trunc.. Hello world.\n");
	close(fd);

	return 0;
}

static int append_file(char *target) {
	int fd;

	fd = open(target, O_WRONLY | O_APPEND, 0644);
	if (fd == -1) {
		printf("open() append fail.\n");
		return -1;
	}

	dprintf(fd, "Append.. Hello world.\n");
	close(fd);

	return 0;
}

int main(int argc, char **argv)
{
	char *target = argv[1];
	if (write_file(target)) {
		printf("write_file() fail.\n");
		return -1;
	}
	printf("write_file() success.\n");
	
	if (trunc_file(target)) {
		printf("trunc_file() fail.\n");
		return -1;
	}
	printf("trunc_file() success.\n");

	if (append_file(target)) {
		printf("append_file() fail.\n");
		return -1;
	}
	printf("append_file() success.\n");

	return 0;
}
