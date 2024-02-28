#include <stdio.h>
#include <stdlib.h>

// 64bit �ü���̱� ������, �޸� 8byte ����

int func2(int a, int b) // a <= b�̸� 0, a > b�̸� 1�� ��ȯ�ϴ� �Լ� 
{
	__asm__ __volatile__ // ����� �ڵ�, �����Ϸ��� ����ȭ���� �ʴ´� 
  	(
		"movl 16(%ebp),%edx \n\t"	// %edx = a
		"movl 24(%ebp),%eax \n\t"	// %eax = b
		"cmpl %eax,%edx \n\t"		// a�� b �� 
		"jle L0 \n\t"				// a�� b���� �۰ų� ������ L0�� ����
		"movl $1,%eax \n\t"			// �ƴϸ� %eax = 1�ϰ�, 
		"jmp L1 \n\t"				// L1���� ����(����)  
	"L0: \n\t"						
		"movl $0,%eax \n\t"			// %eax = 0
	"L1: \n\t"						// �Լ� ����
	);
}
void func1(int *a, int *b) // swap �Լ� 
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
	 
	int arr[] = { 1, 9, 5, 6, 3, 2, 9, 4, 1, 3 }; // ������ �迭 
	
	// Fill your own codes from here
	
	int len = sizeof(arr) / sizeof(arr[0]); // �迭 ���� len 
	int i, j, min; // �����Ϸ��� C99�� �ƴϱ� ������ for���� �ʱ�Ŀ��� ����x 
	
	// Sort arr
	// YOU MUST USE func1, func2 
	
	// ���� ���� 
	for(i = 0; i < len-1; i++) { // ������ ��Ҵ� �̹� ���ĵǾ� �ֱ� ������ ������ �ʿ� ���� 
		min = i; // �� �ݺ����� ó�� min�� i�� ����, 
		
		// �� �ݺ����� ���� ���� ���� ã�´�
		for(j = i+1; j < len; j++) {
			if(func2(arr[min], arr[j])) { // arr[min] > arr[j]�̸� 
				min = j; // min�� �� ���� ���� �ε��� j�� ����
			}
		}
		func1(&arr[min], &arr[i]); // �� �ݺ����� i��° ���� ���� ���� ���� �ٲ۴�
	}
	
	// Output MUST be
	// 1 1 2 3 3 4 5 6 9 9	
	for(i = 0; i < len; i++) { // ���ĵ� �迭 ��� 
		printf("%d ", arr[i]);
	}

	return 0;
}
