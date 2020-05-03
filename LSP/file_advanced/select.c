/**
*	@file		select.c			
*	@manual		observe the status about multiple file descriptor.	
*	@brief		read buffer from multiple fd.	
*	@reference	:!man 2 select	
*	@functions	
*
*	@author		yamp
*	@date		Apr 26, 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/stat.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int fdGen() {
	int ret;
	ret = inotify_init();
	if (ret == -1) {
		printf("inotify_init() fail.\n");
		return -1;
	}
	return ret;
}

int watchSet(int *fd, char *pathName) {
	int wd = inotify_add_watch(*fd, pathName, IN_CREATE | IN_DELETE);
	if (wd == -1) {
		printf("inotify_add_watch() about [%s] fail.\n", pathName);
		return -1;
	}
	return wd;
}

int watchEvent(int fds[2]) {
	char buf[1024];
	memset(buf, 0, sizeof(buf));

	#if 0
	int res = read(fds[0], buf, sizeof(buf));
	if (res == -1) {
		printf("read() fail.\n");
		return -1;
	}
	#endif

	#if 1
	// fd set을 각 fd에 대해 초기화 후 set하기.
	// fd set 처리
	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(fds[0], &fdSet);
	FD_SET(fds[1], &fdSet);

	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	
	// 읽는 부분에 관심 있으므로 쓰는 부분, ~ 부분은 NULL로 처리.
	// fd 중에 가장 큰 값에 1을 더해준 값을 가장 먼저 넣기.
	// return 값은 읽어온 개수. 0을 리턴 시 타임 아웃. 실패시 -1
	int selRet = select(MAX(fds[0], fds[1]) + 1, &fdSet, NULL, NULL, &timeout); 
	#endif
	

	if (selRet < 0) {
		printf("select() fail\n");
		return -1;
	}
	else if (selRet == 0) {
		printf("select() timeout occur!!\n\n");
		return 0;
	}
	
		// 폴더에서 watch하는 부분
	if (FD_ISSET(fds[0], &fdSet)) {
		int res = read(fds[0], buf, sizeof(buf));
		if (res == -1) {
			printf("fds[0] read() fail.\n");
			return 0;
		}
		struct inotify_event *event = (struct inotify_event *) &buf[0];
		while (res > 0) {
			if (event->mask & IN_CREATE) {
				printf("file [%s] is created\n", event->name);
			}
			if (event->mask & IN_DELETE) {
				printf("file [%s] is deleted\n", event->name);
			}
			uint32_t eventStructLen = sizeof(struct inotify_event) + event->len;
			event = (struct inotify_event *)(char *)event + eventStructLen;
			res -= eventStructLen;
		}
	}
	else if (FD_ISSET(fds[1], &fdSet)) {
		memset(buf, 0, sizeof(buf));
		int res = read(fds[1], buf, sizeof(buf));
		if (res == -1) {
			printf("fds[1] read() fail.\n");
			return 0;
		}
		printf("terminal input: %s\n", buf);
	}

	return 0;
}

int main(int argc, char **argv) {
	int fds[2] = { 0, };

	fds[0] = fdGen();	
	if (fds[0] == -1) goto err;

	fds[1] = STDIN_FILENO;
	
	int wds[2] = { 0, };
	wds[0] = watchSet(&fds[0], ".");
	wds[1] = watchSet(&fds[0], "../file_basic");
	if (wds[0] == -1 || wds[1] == -1) goto err;

	while(1) {
		if(watchEvent(fds)) goto err;		
	}

	for (int i = 0; i < 2; ++i) {
		close(fds[i]);
		close(wds[i]);
	}
	return 0;

err:
	printf("detected error.\n");
	for (int i = 0; i < 2; ++i) {
		if(fds[i] >= 0) close(fds[i]);
		if(wds[i] >= 0) close(wds[i]);
	}
	return -1;
}

