/**
*	@file		flock.c			
*	@manual		enter the file name to lock and lock mode.	
*				compare the lock modes
*	@brief		using lock shared, exclusive mode.	
*	@reference	:!man 2 flock		
*	@functions	flock, 
*
*	@author		yamp
*	@date		Apr 27, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>

static void print_usage(void) {
	printf("enter 'sh'/'ex'/'shnb'/'exnb' as an argument\n");
	exit(-1);
}

// sh: 수행되는 모든 파일에서 lock을 잡을 수 있음
// ex: 가장 먼저 수행된 파일만 lock을 잡을 수 있음. 그 외에는 대기상태.
// non-block: lock을 잡을 수 없을 때, 대기하지 않고 바로 종료하게 됨. 
int file_lock(char *target, char *mode) {
	int fd = open(target, O_CREAT | O_RDWR, 0644);
	if (fd < 0) {
		printf("open() fail.\n");
		return -1;
	}
	printf("open() success.\n");

	int ops;
	if (!strcmp(mode, "sh"))		ops = LOCK_SH;
	else if (!strcmp(mode, "ex"))	ops = LOCK_EX;
	else if (!strcmp(mode, "shnb")) ops = LOCK_SH | LOCK_NB;
	else if (!strcmp(mode, "exnb")) ops = LOCK_EX | LOCK_NB;
	else print_usage();

	printf("trying to grab the lock\n");
	if (flock(fd, ops)) {
		printf("flock(ops %d) fail.\n", ops);
		goto out;
	}
	printf("grab the lock!\n");
	getc(stdin);

	if(flock(fd, LOCK_UN)) {
		printf("flock(unlock) fail.\n");
		goto out;
	}

	close(fd);
	return 0;

out:
	close(fd);
	return -1;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		print_usage();
	}
	
	if (file_lock(argv[1], argv[2])) {
		printf("file_lock() fail.\n");
		return -1;	
	}	


	return 0;
}
