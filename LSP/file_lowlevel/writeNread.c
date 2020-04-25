#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Byte type write and read

#define TARGET_FILE "doc_writeNread.txt"

struct person {
	char name[10];
	int age;
};

#define GROUP_SIZE (2)

static int write_info(struct person *p) {
	int fd;
	// return type of write: ssize
	ssize_t ret;

	fd = open(TARGET_FILE, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}
	
	// p에 있는 값을 size만큼 쓰기. 잘 써지면 struct person개 써짐.
	ret = write(fd, p, sizeof(struct person));
	if (ret == -1) {
		goto err;
	}
	else if (ret != sizeof(struct person)) {
		printf("partial read.\n");
		goto err;
	}
	
	close(fd);	

	return 0;

err:
	printf("write() fail. \n");
	close(fd);
	return -1;
}

static int read_info(void) {
	int fd;
	ssize_t ret;
	
	fd = open(TARGET_FILE, O_RDONLY);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}

	// until aproach EOF
	while (1) {
		struct person p;
		ret = read(fd, &p, sizeof(struct person));
		if (ret == -1) {
			goto err;
		}
		// EOF 조건을 오류 조건보다 앞에 쓰기
		else if (ret == 0) {
			printf("approach EOF.\n");

			FILE *fp;
			if(!(fp = fdopen(fd, "r"))) {
				printf("fdopen() fail.\n");
				close(fd);
				return -1;
			}
			printf("file position: %ld\n", ftell(fp));
			fclose(fp);
			break;	
		}
		else if (ret != sizeof(struct person)) {
			printf("partial read.\n");
			goto err;
		}
		printf("name: %s, age: %d\n", p.name, p.age);
	}
	// 성공한 경우
	close(fd);
	return 0;

err:
	printf("read() fail.\n");
	close(fd);
	return -1;
}

int main(int argc, char **argv) {
	struct person group[2] = {
		{"kim", 26},
		{"lee", 24}
	};

	for (int i = 0; i < GROUP_SIZE; ++i) {
		if(write_info(&group[i])) {
			printf("write_info() fail.\n");
			return -1;
		}
	} 
	printf("write_info() success!\n");
	
	if (read_info()) {
		printf("read_info() fail.\n");
		return -1;
	}
	printf("read_info() success!\n");

	return 0;
}
