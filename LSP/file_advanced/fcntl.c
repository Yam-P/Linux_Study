/**
*	@file		fcntl.c	
*	@manual		call file data from using read in case of blocking/non-blocking mode
*	@brief		using blocking mode, wait stdin input
*				after changing blocking mode to non-blocking mode, it don't wait the input.
*	@reference	:!man 2 read
*				:!man 2 fcntl	
*	@functions	fcntl 	
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
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv) {
	int fd = STDIN_FILENO; 
	#if 0
	int fd = open("hi.txt", O_RDONLY);
	if (fd == -1) {
		printf("open() fail.\n");
		return -1;
	}
	#endif

	char buf[128];
	memset(buf, 0, sizeof(buf));
	// read()는 성공시, 읽은 글자의 byte를, 실패시 -1을 반환.
	printf("trying to read with blocking mode\n");
	int	ret = read(fd, buf, sizeof(buf));
	printf("read(): %s:%d bytes\n", buf, ret);
	// stdin을 file descriptor로 사용하여 사용자로부터 input 받음

	// file 지정자에 대한 flag를 받아오기.
	int flag = fcntl(fd, F_GETFL);
	if (flag == -1) {
		printf("fcntl(F_GETFL) fail.\n");
		return -1;
	} 

	// flag 다시 세팅. 이전에 받아온 플래그 값을 이용.
	flag = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
	if (flag == -1) {
		printf("fcntl(F_SETFL) fail.\n");
		return -1;
	}
	
	// fd는 stdin 이기 때문에 빈 값이므로 바로 error return.
	// 다시 동기화 모드부터 시작하고 싶으면 창을 껏다 켜기.
	memset(buf, 0, sizeof(buf));
	printf("trying to read with non-blocking mode\n");	
	ret = read(fd, buf, sizeof(buf));
	printf("read(): %s:%d bytes\n",  buf, ret);
	if (ret == -1) {
		printf("errno = %d, %s\n", errno, strerror(errno));
	}

	return 0;
}
