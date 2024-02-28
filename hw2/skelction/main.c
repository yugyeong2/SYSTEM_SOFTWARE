#include <stdio.h>
#include <stdlib.h>

// 64bit 운영체제이기 때문에, 메모리 8byte 단위

int func2(int a, int b) // a <= b이면 0, a > b이면 1을 반환하는 함수 
{
	__asm__ __volatile__ // 어셈블리 코드, 컴파일러가 최적화하지 않는다 
  	(
		"movl 16(%ebp),%edx \n\t"	// %edx = a
		"movl 24(%ebp),%eax \n\t"	// %eax = b
		"cmpl %eax,%edx \n\t"		// a와 b 비교 
		"jle L0 \n\t"				// a가 b보다 작거나 같으면 L0로 점프
		"movl $1,%eax \n\t"			// 아니면 %eax = 1하고, 
		"jmp L1 \n\t"				// L1으로 점프(종료)  
	"L0: \n\t"						
		"movl $0,%eax \n\t"			// %eax = 0
	"L1: \n\t"						// 함수 종료
	);
}
void func1(int *a, int *b) // swap 함수 
{
	__asm__ __volatile__
  	(
		"movl 24(%ebp),%ecx \n\t"	// %ecx = b
		"movl 16(%ebp),%edx \n\t"	// %edx = a
		"movl (%ecx),%eax \n\t"		// %eax = *b
		"movl (%edx),%ebx \n\t"		// %ebx = *a
		"movl %eax,(%edx) \n\t"		// (%edx) = *a = *b = %eax
		"movl %ebx,(%ecx) \n\t"		// (%ecx) = *b = *a = %ebx
	);
}

int main(int argc, char *argv[]) {
	 
	int arr[] = { 1, 9, 5, 6, 3, 2, 9, 4, 1, 3 }; // 정렬할 배열 
	
	// Fill your own codes from here
	
	int len = sizeof(arr) / sizeof(arr[0]); // 배열 길이 len 
	int i, j, min; // 컴파일러가 C99가 아니기 때문에 for문의 초기식에서 정의x 
	
	// Sort arr
	// YOU MUST USE func1, func2 
	
	// 선택 정렬 
	for(i = 0; i < len-1; i++) { // 마지막 요소는 이미 정렬되어 있기 때문에 정렬할 필요 없다 
		min = i; // 각 반복에서 처음 min를 i로 놓고, 
		
		// 각 반복마다 가장 작은 수를 찾는다
		for(j = i+1; j < len; j++) {
			if(func2(arr[min], arr[j])) { // arr[min] > arr[j]이면 
				min = j; // min을 더 작은 수의 인덱스 j로 변경
			}
		}
		func1(&arr[min], &arr[i]); // 각 반복마다 i번째 수를 가장 작은 수와 바꾼다
	}
	
	// Output MUST be
	// 1 1 2 3 3 4 5 6 9 9	
	for(i = 0; i < len; i++) { // 정렬된 배열 출력 
		printf("%d ", arr[i]);
	}

	return 0;
}
