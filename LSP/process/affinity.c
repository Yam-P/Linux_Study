/**
*	@file		: affinity.c	
*	@manual		: !man SCHED_GETAFFINITY
				: !man CPU_ZERO
*	@brief		: get # of operating process and print it
				: change the set(order) of cpu and check whole process
*	@reference	
*	@functions	: CPU_SET, sched_getaffinity, sched_setaffinity	
*
*	@author		yamp
*	@date		June 16, 2020
*/
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <sched.h> 

#define MAXCPU 10
int print_cpuset(cpu_set_t *mask) {
	printf("Operating CPU: ");
	int cnt = 0;
	for (int i = 0; i < MAXCPU; ++i) {
		// mask 주소가 수행하고 있는 CPU가 맞는지 확인
		// cpu 확인하는 명령어: cat /proc/cpuinfo
		if (CPU_ISSET(i, mask)) {
			++cnt;
			printf("%d ", i);
		}
	}
	printf("\n");
	
	return cnt;
}

int main(int argc, char **argv) {
	// 현재 pid를 어느 processor에서 수행할 수 있는지 확인
	// mask 값에 할당된 cpu 번호를 씌우고, 이를 확인하는 
	int cur_cpu;
	cpu_set_t mask;
	if(sched_getaffinity(getpid(), sizeof(cpu_set_t), &mask)) {
		perror("sched_getaffinity()\n");
		return -1;
	}
	int num_cpus = print_cpuset(&mask);

	cur_cpu = sched_getcpu();
	printf("run on CPU (before change): %d\n", cur_cpu);

	// Initialize the mask
	CPU_ZERO(&mask);
	CPU_SET((cur_cpu + 1) % num_cpus, &mask);
	if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask)) {
		perror("sched_setaffinity()\n");
		return -1;
	}

	sleep(2);

	cur_cpu = sched_getcpu();
	printf("run on CPU (after change): %d\n", cur_cpu);	

	return 0;
}
