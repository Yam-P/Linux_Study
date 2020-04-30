/**
*	@file		mread.c	
*	@manual		enter file name as argument	
*				read file using memory map	
*	@brief		using file descriptor and mmap, read the file
*				to obtain the size of file, use fstat		
*	@reference	:!man 2 mmap	
*				:!man 2 fstat
*	@functions	open, close, mmap	
*
*	@author		yamp
*	@date		Apr 27, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>	

struct person {
	char name[20];
	int age;
};


static int write_info(char *target, struct person *p) {
	int fd = open(target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == - 1) {
		printf("open() fail.\n");
		return -1;
	}
	
	ssize_t ret = write(fd, p, sizeof(struct person));
	if (ret == -1 || ret != sizeof(struct person)) {
		goto err;
	}

	close(fd);
	return 0;

err:
	printf("write() fail.\n");
	close(fd);
	return -1;
}

#if 1
static int read_info(char *target) {
	int fd = open(target, O_RDONLY);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}	
	
	// to obtain the size of file, use fstat()
	// fstat은 file descriptor를 사용하기 때문.
	// statBuf의 멤버인 st_size를 사용할 것.
	struct stat statBuf;
	if(fstat(fd, &statBuf)) {
		printf("fstat() fail.\n");
		close(fd);
		return -1;
	}
	
	/*
    void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);	
	*/
	// mode: read, flag: shared, offset: 0
	// 성공시 주소 데이터 반환, 실패시 MAP_FAILED 반환
	int fileSize = statBuf.st_size;
	struct person *p = mmap(NULL, statBuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		printf("mmap() fail\n");
		close(fd);
		return -1;
	}
	
	// file 전체의 메모리주소를 매핑해온 후, 포인터로 접근하는 방식.
	int iterMax = fileSize / sizeof(struct person);	
	for (int i = 0; i < iterMax; ++i) {
		printf("name: %s, age: %d\n", p[i].name, p[i].age);
	}
	
	close(fd);
	return 0;
}
#endif

#define GROUP_SIZE (2)
int main(int argc, char **argv) {
	char *target = argv[1];

	struct person group[GROUP_SIZE] = {
		{"kim", 26},
		{"lee", 24}	
	};
	
	for (int i = 0; i < GROUP_SIZE; ++i) {
		if (write_info(target, &group[i])) {
			printf("write_info() fail.\n");
			return -1;
		}
	}
	printf("write_info() success.\n");

	if (read_info(target)) {
		printf("read_info() fail.\n");
		return -1;
	}
	printf("read_info() success.\n");

	return 0;
}
