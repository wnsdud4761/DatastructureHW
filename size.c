//size.c
#include <stdio.h>
#include <stdlib.h>

void main(){
    int **x;

    printf("[----- [오준영] [2017038074] -----]\n");

    printf("sizeof(x) = %lu\n", sizeof(x));
    printf("sizeof(*x = %lu\n", sizeof(*x));
    printf("sizeof(**x = %lu\n", sizeof(**x));
}
// 포인터의 크기의 경우 32bit로 컴파일 했기 때문에 4bit로 고정된다. 
// 따라서 4bit로 출력
