/**
*	@file		fcntl.c	
*	@manual		call file data from using read in case of blocking/non-blocking mode
*	@brief		using blocking mode, wait stdin input
*				after changing blocking mode to non-blocking mode, it don't wait the input.
*	@reference	:!man 2 read
*				:!man 2 fcntl	
*	@functions	fcntl, 	
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


int main(int argc, char **argv) {
	int fd = STDIN_FILENO; 

	char buf[128];
	memset(buf, 0, sizeof(buf));
	// read()는 성공시, 읽은 글자의 byte를, 실패시 -1을 반환.
	int	ret = read(fd, buf, sizeof(buf));
	// stdin을 file descriptor로 사용하여 사용자로부터 input 받음

	// file 지정자에 대한 flag를 받아오기.
	int flag = fcntl(fd, F_GETFL);
	if (flag

	return 0;
}
