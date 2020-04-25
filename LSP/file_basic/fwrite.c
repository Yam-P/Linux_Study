#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char title[30] = "doc_person.txt";

struct person
{
	char name[20];
	int age;
};

#define MAX_SIZE (2)

struct person friends[MAX_SIZE];
void genInfo(void) {
	struct person kim = {
		.name = "kim",
		.age = 20
	};
	struct person lee = {
		.name = "lee",
		.age = 30
	};
	friends[0] = kim;
	friends[1] = lee;
}

static int write_to_file(void) 
{
	FILE *fp;

	if (!(fp = fopen(title, "w"))) {
		return -1;
	}

	genInfo();		
	for (int i = 0; i < MAX_SIZE; ++i) {
		// fwrite는 성공한 쓰기 횟수를 반환. 한번 쓰므로 1이면 만족.
		// 기록할 데이터의 개수는 1이므로, sizeof 다음 1
		if (fwrite(&friends[i], sizeof(struct person), 1,  fp) != 1) {
			goto err;
		}
	}

	fclose(fp);
	return 0;

// 예외처리 구문 추가
err:
	// 만약 파일이 아직 열려있다면, 닫고 -1 반환
	if (fp) fclose(fp);
	return -1;
}

static int read_from_file(void) 
{
	FILE *fp;
	if(!(fp = fopen(title, "r"))) {
		return -1;
	}

	struct person info[MAX_SIZE];
	// 두번 읽어오게 될 것.
	if(fread(info, sizeof(struct person), MAX_SIZE, fp) != MAX_SIZE) {
		goto err;
	}
	
	fclose(fp);

	for (int i = 0; i < MAX_SIZE; ++i) {
		printf("name: %s, age: %d\n",
				info[i].name,
				info[i].age);
	}

	return 0;

err:
	if (fp) fclose(fp);
	return -1;
}

int main(int arc, char **argv)
{
	if(write_to_file()) {
		printf("file write fail.\n");
		return -1;
	}
	printf("file write success.\n");

	if (read_from_file()) {
		printf("file read fail.\n");
		return -1;
	}
	printf("file read success.\n");

	return 0;
}
