#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); // 행렬 생성 함수
void print_matrix(int** matrix, int row, int col); // 행렬 출력 함수
int free_matrix(int** matrix, int row, int col); // 행렬을 생성하고 할당된 메모리를 free시켜주는 함수
int fill_data(int** matrix, int row, int col); // 행렬의 data를 채워넣는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬의 합을 구하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬의 차를 구하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 전치행렬을 구하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬의 곱을 구하는 함수

int main()
{
    char command; // 명령어 입력을 통해 두 행렬의 연산을 결정
    printf("[----- [오준영]  [2017038074] -----]\n");

	int row, col; 
	srand(time(NULL)); // 행렬 안 data들의 값을 난수로 설정하여 무작위로 결정

	printf("Input row and col : ");
	scanf("%d %d", &row, &col); // 행과 열의 숫자를 입력받는다.
    int** matrix_a = create_matrix(row, col); // 행렬 a 생성
	int** matrix_b = create_matrix(row, col); // 행렬 b 생성
    int** matrix_a_t = create_matrix(col, row); // 행렬 a_t 생성 (row와 col의 위치를 바꾸어 생성)

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) {return -1;}

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);
			fill_data(matrix_b, row, col);
			break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col);
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);
			break; 
        case 'a': case 'A':
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break; 
        case 's': case 'S':
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
        case 't': case 'T':
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
			break;
        case 'm': case 'M':
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}
	}
    while(command != 'q' && command != 'Q');

	return 1;
} // 각 명령어를 case문을 통해 나누고 do while문을 이용하여 반복되도록 설정

int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return NULL;
	} // row와 col의 사이즈를 통해 오류메시지를 출력 

	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (int r = 0; r < row; r++) {
		matrix[r] = (int*)malloc(sizeof(int) * col);
	} // 행렬 생성

	if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return NULL;
	} // matrix가 비어있을 경우 할당이 실패했다고 오류메시지 출력

	return matrix; // 행렬 생성 후 생성된 행렬 리턴
}


void print_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			printf("%3d ", matrix[matrix_row][matrix_col]);
		printf("\n");
	} // matrix의 값들을 행렬의 형태로 출력
	printf("\n");
	
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return;
	}

	return;
}

int free_matrix(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		free(matrix[matrix_row]);
	}

	free(matrix);
	return 1;
} // 동적할당을 통해 받은 행렬의 메모리를 free해주는 함수

int fill_data(int** matrix, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}

    for (int matrix_row = 0; matrix_row < row; matrix_row++)
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix[matrix_row][matrix_col] = rand() % 20;
    
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	return 1;
} // 임의로 생성된 난수를 행렬의 값으로 채우는 함수

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sum = create_matrix(row, col);
	
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
	}
	
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	print_matrix(matrix_sum, row, col);
	free_matrix(matrix_sum, row, col);
	return 1;
} // 행렬의 합을 계산하는 함수로 matrix_sum이라는 행렬 속에 두 행렬의 합을 저장한 뒤 출력

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** matrix_sub = create_matrix(row, col);
	
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
	}
	
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_sub, row, col);
	free_matrix(matrix_sub, row, col);

	return 1;
} // 행렬의 차를 계산하는 함수로 matrix_sub라는 행렬 속에 두 행렬의 차를 저장한 뒤 출력

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	
    for (int matrix_row = 0; matrix_row < row; matrix_row++) {
		for (int matrix_col = 0; matrix_col < col; matrix_col++)
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row];
	}
	
    if (matrix == NULL || matrix_t ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}

	return 1;
} //전치 행렬을 구하는 함수로 행렬의 원소들을 대각선축을 기준으로 서로 위치를 바꾸는 함수

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** matrix_axt = create_matrix(row, row);
	
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) {
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++)
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row];
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
	}
	print_matrix(matrix_axt, row, row);
	free_matrix(matrix_axt, row, col);
	return 1;
} // 행렬의 곱을 구하는 함수로 matrix_t를 이용하여 곱을 구한 뒤 출력
