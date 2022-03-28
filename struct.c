//struct.c
#include <stdio.h>
struct student1{
    char lastName;
    int studentId;
    char grade;
};
typedef struct{
    char lastName;
    int studentId;
    char grade;
} student2;
int main(){
    printf("[----- [오준영] [2017038074] -----]\n");

    struct student1 st1 = {'A', 100, 'A'};

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'};

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3; 

    st3 = st2;

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade);

    /* equality test 
    if(st3 == st2) 
        printf("equal\n");
    else
        printf("not equal\n");
    */
    return 0;
}
// 구조체 선언후 구조체의 전부가 아닌 그 안의 필요한 변수만 필요할경우
// 선언한 구조체 이름.구조체 안의 설정한 변수명  을 통해 출력 가능
