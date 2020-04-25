#include <stdio.h>
#include <string.h>

char title[30] = "doc_fpointer.txt";
static int create_file(void) {
	FILE *fp;
	
	if(!(fp = fopen(title, "w"))) {
		printf("fopen() fail\n");
		return -1;
	}

	// ftell은 file pointer의 position을 말해줌.
	printf("after fopen(). offset=%ld\n", ftell(fp));
	fputs("hello world\n", fp);
	fputs("hello world!\n", fp);
	fputs("hello world!!\n", fp);
	fputs("hello world!!!\n", fp);
	printf("before fclose(). offset=%ld\n", ftell(fp));

	fclose(fp);

	return 0;
}

static int read_file(void) {
	FILE *fp;
	char buf[1024];
	
	// r+ 읽은 후 수정 가능
	if (!(fp = fopen(title, "r+"))) {
		perror("fopen() fail\n");
		return -1;
	}
	
	printf("----------------------\n");
	printf("after fopen(). offset=%ld\n", ftell(fp));
	memset(buf, 0, sizeof(buf));
	// 한줄에 대해서만 적용. 
	// 추후 예외처리 필요
	fgets(buf, sizeof(buf), fp);
	printf("after fgets(). offset=%ld\n", ftell(fp));
	printf("----------------------\n");
	fseek(fp, 0, SEEK_END);
	printf("after fseek(). offset=%ld\n", ftell(fp));
	fputs("final\n", fp);
	printf("after fputs(). offset=%ld\n", ftell(fp));
	
	return 0;
}



int main (int argc, char **argv) {
	create_file();
	read_file();	

	return 0;
}
