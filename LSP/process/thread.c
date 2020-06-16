/**
*	@file		: thread.c		
*	@manual		: !man pthread_create
				: !man pthread_join
*	@brief		: make two thread and observe operation of two thread 
				  to carry out one commen action (child_thread_main)
				: shared source will be add/sub operatoin without/with mutex.
				  without mutex, it has wrong value becase of interference.
*	@reference	: Warning -> for compiling, add -pthread library in Makefile	
*	@functions	: pthread_create, pthread_join, ptrhead_self	
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

#include <pthread.h>

// 공유 자원 만들기
#define MAX_TRY 10000000
int shared = 0;
#define WITH_MUTEX 1
pthread_mutex_t mutex;

// shared action
void *child_thread_main(void *arg) {
	// 자신 thread의 아이디를 가지고오기: pthread_self
	printf("created child pthread id: %lu\n", pthread_self());

#if WITH_MUTEX
	pthread_mutex_lock(&mutex);
#endif

	for (int i = 0; i < MAX_TRY; ++i) ++shared; 
	for (int i = 0; i < MAX_TRY; ++i) --shared; 

#if WITH_MUTEX
	pthread_mutex_unlock(&mutex);
#endif

	return NULL;
}

// thread 생성
int yamp_thread_create(pthread_t *child_thread) {
	int ret = pthread_create(child_thread, NULL, child_thread_main, NULL);
	if (ret) {
		printf("pthread_create() fail(%d)\n", ret);
		return -1;
	}
	return 0;
}

// thread 끝 기다리기 (fork wait과 유사)
int yamp_thread_join(pthread_t *child_thread) {
	printf("trying to join %lu\n", *child_thread);
	if (pthread_join(*child_thread, NULL)) {
		printf("pthread_join(%lu) fail\n", *child_thread);
		return -1;
	}
	return 0;
}

int main(int argc, char **argv) {
	// 두개의 자식 thread를 만들기
	pthread_t child_threads[2];
	if (pthread_mutex_init(&mutex, NULL)) {
		printf("mutex init fail\n");
		return -1;
	}

	printf("main  pthread id: %lu\n", pthread_self());
	if(yamp_thread_create(&child_threads[0])) return -1;
	if(yamp_thread_create(&child_threads[1])) return -1;
	printf("\n");

	
	if(yamp_thread_join(&child_threads[0])) return -1;
	if(yamp_thread_join(&child_threads[1])) return -1;

	printf("shared source: %d\n", shared);
	printf("Done.\n");

	return 0;
}
