/**
*	@file		fwrite.c
*	@manual		input file name using cmd arg
*	@brief		write and read with byte unit. 
				use sizeof() for dealing with byte. 	
*	@functions	fwrite, fread
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct person
{
	char name[20];
	int age;
};

#define MAX_SIZE (2)

struct person friends[MAX_SIZE];
void genInfo(void) {
	struct person kim = {
		.name = "kim",
		.age = 20
	};
	struct person lee = {
		.name = "lee",
		.age = 30
	};
	friends[0] = kim;
	friends[1] = lee;
}

static int write_to_file(char *target) {
	FILE *fp;

	if (!(fp = fopen(target, "w"))) {
		return -1;
	}

	genInfo();		
	for (int i = 0; i < MAX_SIZE; ++i) {
		// fwrite는 성공한 쓰기 횟수 반환. 변수 한 개를 write. 1이면 만족.
		// 기록할 데이터의 개수는 1이므로, size 입력후 1 대입.
		if (fwrite(&friends[i], sizeof(struct person), 1,  fp) != 1) {
			goto err;
		}
	}

	fclose(fp);
	return 0;

// 예외처리 구문 추가
err:
	// 만약 파일이 아직 열려있다면, 닫고 -1 반환
	if (fp) fclose(fp);
	return -1;
}

static int read_from_file(char *target) {
	FILE *fp;

	if(!(fp = fopen(target, "r"))) {
		return -1;
	}

	struct person info[MAX_SIZE];
	// 읽어서 info에 넣기.
	// 두번 읽어오게 될 것.
	if(fread(info, sizeof(struct person), MAX_SIZE, fp) != MAX_SIZE) {
		goto err;
	}
	
	fclose(fp);

	// display contents of file
	for (int i = 0; i < MAX_SIZE; ++i) {
		printf("name: %s, age: %d\n", info[i].name, info[i].age);
	}

	return 0;

err:
	if (fp) fclose(fp);
	return -1;
}

int main(int arc, char **argv) {
	char *target = argv[1];
	if(write_to_file(target)) {
		printf("write_to_file() fail.\n");
		return -1;
	}
	printf("write_to_file() success.\n");

	if (read_from_file(target)) {
		printf("read_from_file fail.\n");
		return -1;
	}
	printf("read_from_file() success.\n");

	return 0;
}
