/**
*	@file		inotify.c			
*	@manual		supervisior two directory's event	
* 				about file creation and deletion
*	@brief		
*	@reference	:!man 2 inotify_init	
*				:!man 7 inotify_init
*				:!man 2 inotify_add_watch
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
#include <sys/inotify.h>

#if 0
struct inotify_event {
	int      wd;       /* Watch descriptor */
	uint32_t mask;     /* Mask describing event */
	uint32_t cookie;   /* Unique cookie associating related
						  events (for rename(2)) */
	uint32_t len;      /* Size of name field */
	char     name[];   /* Optional null-terminated name */
};
#endif
int main(int argc, char **argv) {

	int fd = inotify_init();
	if (fd == -1) {
		printf("inotify_init() fail.\n");
		return -1;
	}

	char *dir1 = ".";
	char *dir2 = "../file_basic";

	int wd1 = inotify_add_watch(fd, dir1, IN_CREATE | IN_DELETE); 
	if (wd1 == -1) {
		printf("inotify_add_witch() about wd1 fail.\n");
		goto err;
	}

	int wd2 = inotify_add_watch(fd, dir2, IN_CREATE | IN_DELETE); 
	if (wd2 == -1) {
		printf("inotify_add_witch() about wd2 fail.\n");
		goto err;
	}

	while(1) {
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		int ret = read(fd, buf, sizeof(buf));
		if (ret == -1) {
			printf("read() fail.\n");
			goto err;
		}
		printf("read() success.\n");

		// buf의 시작점을 event 포인터로 가지고 오도록 casting
		struct inotify_event *event = (struct inotify_event *) &buf[0];
		while (ret > 0) {
			if (event->mask & IN_CREATE) {
				printf("file [%s] is created\n", event->name);
			}
			if (event->mask & IN_DELETE) {
				printf("file [%s] is deleted\n", event->name);
			}
			// 다음 event의 주소를 지목
			uint32_t eventStructLen = sizeof(struct inotify_event) + event->len;
			event = (struct inotify_event *)(char *)event + eventStructLen; 
			// event를 모두 읽고 빠져나와야 하므로.
			ret -= eventStructLen;
		}	
	}	

	close(wd1);
	close(wd2);
	close(fd);

	return 0;
err:
	// 제대로 열린 descriptor가 있다면 종료하고 프로그램 닫기.
	if (fd >= 0) {
		close(fd);
	}
	if (wd1 >= 0) {
		close(wd1);
	}
	if (wd2 >= 0) {
		close(wd2);
	}
	printf("program terminated!\n");
	return -1;
}
