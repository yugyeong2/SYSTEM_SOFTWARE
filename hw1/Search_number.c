#include <stdio.h>
#include <Stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct Node
{
    char data[100];
    struct Node *link;
} listNode;

// 헤드 구조체
typedef struct Head
{
    struct Node *first;
} headNode;

void insertNode(headNode *head, char data[100]); // 노드를 삽입할 함수
void freeList(headNode *head);                   // 메모리 동적할당을 해제할 함수

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

    char buf[100] = {0};         // temporary storage
    fgets(buf, sizeof(buf), fp); // input data
    buf[strcspn(buf, "\n")] = '\0';

    // initialize singly-linked-list
    headNode *head = (headNode *)malloc(sizeof(headNode));
    listNode *node = (listNode *)malloc(sizeof(listNode));
    strcpy(node->data, buf);
    node->link = NULL;
    head->first = node; // 헤드는 첫 번째 노드를 가리킨다
    only_one_count++;

    while (!feof(fp)) // 파일의 끝에서 0 반환
    {
        fgets(buf, sizeof(buf), fp); // input data
        buf[strcspn(buf, "\n")] = '\0';

        insertNode(head, buf);
    }

    printf("Only one count : %d\n", only_one_count);
    printf("Near prime count : %d", near_prime_count);

    free(head);
    fclose(fp);
    return 0;
}

// 중복을 확인하는 함수
void insertNode(headNode *head, char data[100])
{
    // 리스트를 탐색할 포인터 p, trail
    listNode *p = head->first;
    listNode *trail = head->first;

    while (p != NULL)
    { // 중복 검사
        if (strcmp(p->data, data) == 0)
        {
            return;
        }
        trail = p;
        p = p->link;
    }

    // 노드 생성
    listNode *node = (listNode *)malloc(sizeof(listNode));
    strcpy(node->data, data);
    node->link = NULL;

    trail->link = node;

    only_one_count++;
}

// 동적할당을 해제하는 함수
void freeList(headNode *head)
{
    listNode *p = head->first;
    listNode *trail = NULL;

    while (p != NULL)
    {
        trail = p;
        p = p->link;
        free(trail);
    }
    free(head);
}