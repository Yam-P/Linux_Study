/**
*	@file		fork.c	
*	@manual		
*	@brief		show the value of pid after/before fork	
*				in here one program, you can observe carrying out 2 process
*	@reference	
*	@functions	
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

void test_func(void) {
	printf("this is a test function(pid: %d)\n", getpid());
}

int main(int argc, char **argv) {
	
	// 현재 프로세스의 pid를 받아오기
	printf("origin process pid: %d\n", getpid());

	// 부모 ps를 자식 ps로 포크 시키기
	pid_t pid = fork();

	if (pid == 0) {
		printf("child ps pid: %d\n", getpid());
	}
	else if (pid > 0) {
		printf("praent ps pid: %d, child ps pid: %d\n", getpid(), pid);
	}

	// 부모/자식 ps 공통으로 수행되는 함수
	test_func();	

	return 0;
}
