//p2-2.c
#include <stdio.h>

void print1(int *ptr, int rows);

int main(){
    int one[] = {0, 1, 2, 3, 4};

    printf("[----- [오준영] [2017038074] -----]\n");

    printf("one = %p\n", one); 
    printf("&one = %p\n", &one);
    printf("&one[0] = %p\n", &one[0]);
    printf("\n");
    print1(&one[0], 5);
    return 0;
}

void print1(int *ptr, int rows){
    /* print out a one-dimensional array using a pointer*/

    int i;
    printf("Address \t Contents\n");
    for(i=0; i<rows; i++)
        printf("%p \t %5d\n", ptr + i, *(ptr + i));
    printf("\n");
}
// 선언한 배열의 이름을 값으로 출력할 경우 주소가 출력된다. 
// 선언한 배열의 이름 + n == 선언한 배열의 이름[n] 과 같다
