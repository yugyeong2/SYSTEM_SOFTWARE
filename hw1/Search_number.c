#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HASH_TABLE_SIZE 100000 // 해시 테이블 크기

// 노드 구조체
typedef struct Node
{
    char data[20];
    struct Node *link;
} listNode;

// 헤드 구조체
typedef struct Head
{
    struct Node *first;
} headNode;

void initialize(FILE *fp, headNode *head);
void insertNode(FILE *fp, headNode *head);   // 노드를 삽입할 함수
int isPrime(int n);                          // 소수 판별 함수
int calculateIntegerValue(const char *data); // 노드 데이터의 정수 값을 계산하는 함수

int only_one_count;   // 총 node의 수
int near_prime_count; // 1을 빼거나 더했을 때, 소수인 정수의 수

int main()
{
    // open file
    FILE *fp = fopen("input.txt", "r");
    // check if the file is open
    if (fp == NULL)
    {
        printf("Unable to open file.");
        return 1;
    }

    // initialize
    headNode *head = (headNode *)malloc(sizeof(headNode));
    initialize(fp, head);

    while (!feof(fp)) // 파일의 끝에서 0 반환
    {
        insertNode(fp, head);
    }

    // 출력
    printf("Only one count : %d \n", only_one_count);
    printf("Near prime count : %d \n", near_prime_count);

    // 실행 시간을 줄이기 위해 free, close 생략
    return 0;
}

void initialize(FILE *fp, headNode *head)
{
    char buf[20];                   // temporary storage
    fgets(buf, sizeof(buf), fp);    // input data
    buf[strcspn(buf, "\n")] = '\0'; // 개행문자 제거

    listNode *node = (listNode *)malloc(sizeof(listNode));
    strcpy(node->data, buf);
    node->link = NULL;
    head->first = node; // 헤드는 첫 번째 노드를 가리킨다

    only_one_count++;
}

void insertNode(FILE *fp, headNode *head)
{
    char buf[20];                   // temporary storage
    fgets(buf, sizeof(buf), fp);    // input data
    buf[strcspn(buf, "\n")] = '\0'; // 개행문자 제거

    // 리스트를 탐색할 포인터 p, trail
    listNode *p = head->first;
    listNode *trail = NULL;

    while (p != NULL)
    { // 중복 검사
        if (strcmp(p->data, buf) == 0)
        {
            return;
        }
        trail = p;
        p = p->link;
    }

    // 노드 생성
    listNode *node = (listNode *)malloc(sizeof(listNode));
    strcpy(node->data, buf);
    node->link = NULL;

    trail->link = node;

    only_one_count++;

    // 1을 빼거나 더했을 때 소수인 정수의 수 계산
    int intValue = calculateIntegerValue(buf);
    if (isPrime(intValue - 1) || isPrime(intValue + 1))
    {
        near_prime_count++;
    }
}

// 소수 판별 함수
int isPrime(int n)
{
    if (n < 2)
    {
        return 0;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

// 노드 데이터의 정수 값을 계산하는 함수
int calculateIntegerValue(const char *data)
{
    return atoi(data); // 모든 문자가 숫자이므로 정수로 변환
}