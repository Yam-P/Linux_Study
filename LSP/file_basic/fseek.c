/**
*	@file		fseek.c
*	@manual		input file name using cmd arg
*	@brief		way to find position of cursor using ftell and file pointer
*	@functions  ftell, fseek
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <string.h>

static int create_file(char *target) {
	FILE *fp;
	
	if(!(fp = fopen(target, "w"))) {
		printf("fopen() fail\n");
		return -1;
	}

	// ftell은 file pointer의 position을 말해줌.
	printf("after fopen(). offset=%ld\n", ftell(fp));
	printf("write some contents.\n");
	fputs("hello world\n", fp);
	fputs("hello world!\n", fp);
	fputs("hello world!!\n", fp);
	fputs("hello world!!!\n", fp);
	printf("before fclose(). offset=%ld\n", ftell(fp));

	fclose(fp);

	return 0;
}

static int read_file(char *target) {
	FILE *fp;
	char buf[1024];
	
	// r+: 읽은 후 수정 가능
	if (!(fp = fopen(target, "r+"))) {
		perror("fopen() fail\n");
		return -1;
	}
	
	printf("----------------------\n");
	printf("after fopen(). offset=%ld\n", ftell(fp));
	memset(buf, 0, sizeof(buf));
	// 한줄에 대해서만 적용. 
	// 추후 예외처리 필요
	fgets(buf, sizeof(buf), fp);
	printf("after fgets(). offset=%ld\n", ftell(fp));
	printf("----------------------\n");
	fseek(fp, 0, SEEK_END);
	printf("after fseek() to approach END. offset=%ld\n", ftell(fp));
	fputs("final\n", fp);
	printf("after fputs(). offset=%ld\n", ftell(fp));
	
	return 0;
}

int main (int argc, char **argv) {
	char *target = argv[1];
	if (create_file(target)) {
		printf("create_file() fail.\n");
	}
	printf("create_file() success.\n");
	
	if (read_file(target)) {
		printf("read_file() fail.\n");
	}
	printf("read_file() success.\n");

	return 0;
}
