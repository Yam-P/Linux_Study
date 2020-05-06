# MakeFile 사용법

## MakeFile 장점

- 각 파일에 수행되는 반복적 명령을 자동화 할 수 있다.
- 프로그램의 구조를 빠르게 파악하여 관리하기 편리하다.
- 단순 반복 작업으로 인해 재작성을 최소화 시킨다.

예시

> 명령어를 이용하여 diary.h 밑에 memo.c, calendar.c, main.c를 사용하는 프로그램 작성  
>
> 1. diary.h 헤더파일 만들기
> 2. 각 source 파일 만들기
> 3. 각 soucre 파일을 object 파일로 만들기.
>	 gcc -c -o file.o file.c 
>    gcc -c file.o file.c   : 컴파일만 수행하고자 할 때 : .c -> .o 
>    gcc -o file.out file.o : 링크를 수행하고자 할 때 : .o -> .out
> 4. object 파일들을 이용하여 실행파일 만들기. 
> 	 gcc -o diary_exe main.o memo.o calendar.o

Makefile 구성

> - 목적파일(Target): 명령어가 수행되어 나온 결과를 저장할 파일  
> - 의존성(Dependancy): .o파일을  만들기 위해 필요한 재료  
> - 명령어(Command): 실행 되어야 할 명령어들  
> - 매크로(Macro): 코드를 단순화 시키기 위한 방법

기본 뼈대

> 1. 매크로 정의
> 2. 타겟 : 의존성
> 3.    (TAB 이후) 명령어

치환하여 사용하기 - 굳이 컴파일 -> 링크 순서로 안해도 됨.

> 내장 환경변수
> - CC: compiler 종류를 받는 옵션
> - CFLAGS: 옵션을 받는 변수
> - TARGET: 목적 파일명을 받는 변수
> 
> 옵션
> CFLAGS = -pendantic : 
> CFLAGS += -std=c11 : 컴파일러 옵션
> CFLAGS += -Wall -Werror : 경로/컴파일 에러가 나타나도록
> $@: 목적파일의 이름을 그대로 사용하려 할 때
> $^: 의존성 파일들 이름을 모두 사용하려 할 때
> $<: 의존성 파일들 중 첫번째 파일의 이름만 사용하려 할 때

생성 규칙을 줄이기

> .c 파일들을 .o 파일들로 모두 치환하기
> .c.o:
> 	(TAB 이후) $(CC) $(CFLAGS) -c $< 
>
> 목적파일들을 array로 한번에 처리하기
> OBJECTS = memo.o main.o calendar.o
> $(TARGET) : $(OBJECTS)
> 	(TAB 이후) $(CC) $(CFLAGS) -o $@ $^
