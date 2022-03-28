//p2-1.c
#include <stdio.h>

#define MAX_SIZE 100

float sum(float[], int);
float input[MAX_SIZE], answer;
int i;
void main(void){
    for(i=0; i<MAX_SIZE; i++)
        input[i] = i;
    printf("[----- [오준영] [2017038074] -----]\n");

    /* for checking call by reference */
    printf("address of input = %p\n", input); // input이라는 배열의 주소를 출력

    answer = sum(input, MAX_SIZE);
    printf("The sum is: %f\n", answer); // sum 함수를 돌리고 나오는 1부터 100까지의 합을 출력
}

float sum(float list[], int n){
    printf("value of list = %p\n", list); // 파라미터로 input이라는 배열의 주소를 출력
    printf("address of list = %p\n\n", &list); //list의 주소를 출력

    int i;
    float tempsum = 0;
    for(i=0; i<n; i++)
        tempsum += list[i];
    return tempsum;
}
