#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TARGET_FILE "doc_open.txt"
static int write_file(void) {
	int fd;
	
	// write only and unless file exists, create the file
	fd = open(TARGET_FILE, O_WRONLY | O_CREAT, 0644);
	if (fd == -1) {
		printf("open() create fail.\n");
		return -1;
	}
	dprintf(fd, "Hello World! %d\n", 123);
	close(fd);
	return 0;
}

// 파일이 비어있지 않다면, 내용을 지우고 덮어쓰기
static int trunc_file(void) {
	int fd;

	fd = open(TARGET_FILE, O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) {
		printf("open() trunc fail.\n");
		return -1;
	}
	
	dprintf(fd, "Trunc.. Hello world.\n");
	close(fd);

	return 0;
}

static int append_file(void) {
	int fd;

	fd = open(TARGET_FILE, O_WRONLY | O_APPEND, 0644);
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
	if (write_file()) {
		printf("write_file() fail.\n");
		return -1;
	}
	printf("write_file() success.\n");
	
	if (trunc_file()) {
		printf("trunc_file() fail.\n");
		return -1;
	}
	printf("trunc_file() success.\n");

	if (append_file()) {
		printf("append_file() fail.\n");
		return -1;
	}
	printf("append_file() success.\n");

	return 0;
}
