/**
*	@file		epoll.c
*	@manual		observe the status about multiple file descriptor.	
*	@brief		read buffer from multiple fd.	
*				fds[0]: observe creation/deletion of "." and "../file_basic" directory.
* 				fds[1]: read buffer from terminal
*	@reference	:!man 7 epoll
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
#include <sys/epoll.h>
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

	// Epoll로 감지하겠다고 세팅하는 부분 ===========================
	// epfd: epoll instance로, epoll 세팅을 담고있는 부분
	int epfd = epoll_create1(0);
	if (epfd == - 1) {
		printf("epoll_create1() fail\n");
		return -1;
	}

	// epoll control API. 읽어오는 부분을 감지하고 싶음.
	struct epoll_event epEvent;
	for (int i = 0; i < 2; ++i) {
		memset(&epEvent, 0, sizeof(epEvent));
		epEvent.events = EPOLLIN;
		epEvent.data.fd = fds[i];
		if(epoll_ctl(epfd, EPOLL_CTL_ADD, fds[i], &epEvent) == -1) {
			printf("%dth epoll_ctl() fail\n", i);
			return -1;
		}
	}
	// =============================================================

	// 5000ms마다 timeout하고 epEvent structure를 읽어오기
	memset(&epEvent, 0, sizeof(epEvent));
	int epRet = epoll_wait(epfd, &epEvent, 1, 5000);
	if (epRet < 0) {
		printf("select() fail\n");
		return -1;
	}
	else if (epRet == 0) {
		printf("select() timeout occur!!\n\n");
		return 0;
	}
	
	// event가 감지된 상태 (epRet > 0)
	// 폴더에서 watch하는 부분	
	// select와 다르게 flag로 확인하는 것이 아니라, 
	// structure에서 어떤 이벤트가 발생하는지 적힌다.
	if (epEvent.data.fd == fds[0]) {
		int res = read(fds[0], buf, sizeof(buf));
		if (res == -1) {
			printf("fds[0] read() fail.\n");
			close(epfd);
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
	else if (epEvent.data.fd == fds[1]) {
		memset(buf, 0, sizeof(buf));
		int res = read(fds[1], buf, sizeof(buf));
		if (res == -1) {
			printf("fds[1] read() fail.\n");
			close(epfd);
			return 0;
		}
		printf("terminal input: %s\n", buf);
	}

	close(epfd);
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

