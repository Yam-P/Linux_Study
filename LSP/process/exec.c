/**
*	@file		exec.c
*	@manual		
*	@brief		show the value of pid after/before fork	
*				using execl(exec list), show shell cmd result
*				wait until terminate child ps
*	@reference	
*	@functions	:!man 3 execl
*				:!man 2 wait
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
#include <sys/wait.h>

void test_func(void) {
	printf("this is a test function(pid: %d)\n", getpid());
}

int main(int argc, char **argv) {
	// 실행순서: 부모 fork > 부모 prog > 자식 prog > 자식 prog 종료 > 부모 prog 종료
	
	// Step1. 현재 프로세스의 pid를 받아오기
	printf("origin process pid: %d\n", getpid());

	// Step2. 부모 ps를 자식 ps로 포크 시키기
	pid_t pid = fork();

	// Step5. 자식 ps 수행
	if (pid == 0) {
		printf("child ps pid: %d\n", getpid());
		// 쉘 환경변수 경로, 자기 process, 그 외의 변수를 넣어주기
		// 변수 다 넣었으면 마지막에 NULL
		if(execl("/bin/ls", "ls", "-al", "../file_basic", NULL) == -1) {
			printf("exec() fail.\n");
			return -1;
		};
	}
	
	// Step3.
	else if (pid > 0) {
		printf("praent ps pid: %d, child ps pid: %d\n", getpid(), pid);
	}

	// Step4. 부모 ps 함수 수행 후 wait로 들어가기
	test_func();	
	int exit_status;
	pid = wait(&exit_status);

	// Step6. 자식 ps 종료 후, 부모 ps 종료까지
	// 오류코드를 반환하는 것과 마찬가지로 exit 상태를 받아서 출력
	// 0을 리턴하면 성공적으로 종료했다는 의미.
	if(WIFEXITED(exit_status)) {
		printf("child %d returns %d\n", pid, WEXITSTATUS(exit_status));
	}
	else {
		printf("child %d is not exited\n", pid);
	}

	return 0;
}
