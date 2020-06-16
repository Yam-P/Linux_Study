/**
*	@file		: signal.c	
*	@manual		: !man signal
				: !man sigprocmask
*	@brief		: When this prog got signal from shell,
				  operate certain action using handler	
*	@reference	
*	@functions	: sigemptyset, sigaddset, sigprocmask, signal	
*
*	@author		yamp
*	@date		June 16, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <signal.h>

// Shell에서 프로그램 종료 확인을 위해 사용해야할 명령
// : killall -s TERM `pidof signal`
// : killall -s INT `pidof signal`
// : 위 두 명령은 막힘. kill -9 `pidof signal`으로 강제종료
void sigterm_handler(int signum) {
	printf("got sigterm..\n");
}

int main(int argc, char **argv) {
	// sigset에 원하는 signal 등록
	// SIGINT는 ^C에 의한 종료를 막음
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_SETMASK, &set, NULL);

	// kill -TERM에 의한 종료 시그널을 받을 때 수행
	signal(SIGTERM, sigterm_handler);
	printf("start of while(1)\n");
	while (1) {
		sleep(1);
	}
	return 0;
}
