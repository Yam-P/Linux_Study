/**
*	@file		write.c
*	@manual		input file name using cmd arg
*	@brief		use file descriptor, write and read with byte unit. 
				use sizeof() for dealing with byte. 	
*	@functions	open, close,fdopen, write, read
*
*	@author		yamp
*	@date		Apr 27, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Byte type write and read

struct person {
	char name[10];
	int age;
};

#define GROUP_SIZE (2)
static int write_info(char *target, struct person *p) {
	int fd = open(target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}
	
	// return type of write: ssize
	// p에 있는 값을 size만큼 쓰기. 잘 써지면 struct person의 크기만큼 써짐.
	ssize_t ret = write(fd, p, sizeof(struct person));
	if (ret == -1) {
		goto err;
	}
	else if (ret != sizeof(struct person)) {
		printf("partial write.\n");
		goto err;
	}
	
	close(fd);	
	return 0;

err:
	printf("write() fail. \n");
	close(fd);
	return -1;
}

static int read_info(char *target) {
	// open으로 file descriptor를 열면 close로 닫기.
	// fdopen을 사용하여 fd를 fp로 사용할 때, fclose 수행시 fd 역시 닫힘.
	int	fd = open(target, O_RDONLY);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}

	// until aproaching EOF
	while (1) {
		struct person p;
		ssize_t	ret = read(fd, &p, sizeof(struct person));
		if (ret == -1) {
			goto err;
		}
		// EOF 조건을 오류 조건보다 앞에 쓰기
		else if (ret == 0) {
			// file stream으로 변환하여 FILE 포인터 기능 사용시
			FILE *fp;
			if(!(fp = fdopen(fd, "r"))) {
				printf("fdopen() fail.\n");
				close(fd);
				return -1;
			}
			printf("fp position: %ld\n", ftell(fp));
			fclose(fp); // file descriptor도 함께 닫힘.
			break;	
		}
		else if (ret != sizeof(struct person)) {
			printf("partial read.\n");
			goto err;
		}
		printf("name: %s, age: %d\n", p.name, p.age);
	}
	// 성공한 경우
	return 0;

err:
	printf("read() fail.\n");
	close(fd);
	return -1;
}

int main(int argc, char **argv) {
	char *target = argv[1];
	struct person group[GROUP_SIZE] = {
		{"kim", 26},
		{"lee", 24}
	};

	for (int i = 0; i < GROUP_SIZE; ++i) {
		if(write_info(target, &group[i])) {
			printf("write_info() fail.\n");
			return -1;
		}
	} 
	printf("write_info() success!\n");
	
	if (read_info(target)) {
		printf("read_info() fail.\n");
		return -1;
	}
	printf("read_info() success!\n");

	return 0;
}
