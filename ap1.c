//ap1.c
#include <stdio.h>
#include <stdlib.h>

void main(){
    int list[5];
    int *plist[5] = {NULL,};

    plist[0] = (int *)malloc(sizeof(int));

    list[0] = 1;
    list[1] = 100;

    *plist[0] = 200;
    
    printf("[----- [오준영] [2017038074] -----]\n");
    
    printf("value of list[0] = %d\n", list[0]); // list의 가장 첫번째 값
    printf("address of list[0] = %p\n", &list[0]); // 첫번째 list의 주소
    printf("value of list = %p\n", list); // list의 값은 주소값으로 나타난다.
    printf("address of list (&list) = %p\n", &list); // list의 주소값을 출력
    printf("----------------------------------------\n\n");
    printf("value of list[1] = %d\n", list[1]); // list의 두번째 값
    printf("address of list[1] = %p\n", &list[1]); // 두번째 list의 주소
    printf("value of *(list+1) = %d\n", *(list + 1)); // list + 1 이 뜻하는 바는 list의 처음 시작에서 다음 칸이라는 뜻
    printf("address of list+1 = %p\n", list+1);

    printf("----------------------------------------\n\n");
    printf("value of *plist[0] = %d\n", *plist[0]);
    printf("&plist[0] = %p\n", &plist[0]);
    printf("&plist = %p\n", &plist);
    printf("plist = %p\n", plist);
    printf("plist[0] = %p\n", plist[0]);
    printf("plist[1] = %p\n", plist[1]);
    printf("plist[2] = %p\n", plist[2]);
    printf("plist[3] = %p\n", plist[3]);
    printf("plist[4] = %p\n", plist[4]);
    
    free(plist[0]);
}
