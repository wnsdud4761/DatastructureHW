//padding.c
#include <stdio.h>

struct student{
    char lastName[13];
    int studentId;
    short grade;
};

int main(){
    struct student pst;

    printf("[----- [오준영] [2017038074] -----]\n");

    printf("size of student = %ld\n", sizeof(struct student));
    printf("size of int = %ld\n", sizeof(int));
    printf("size of short = %ld\n", sizeof(short));

    return 0;
}
// 구조체의 크기는 선언해 놓은 자료형들의 크기 중 가장 큰 크기를 기준으로 메모리를 잡게된다.
// int => 4의 배수로 크기를 잡는다 따라서 24로 출력
