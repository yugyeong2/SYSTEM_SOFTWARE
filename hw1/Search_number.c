#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 100
#define HASH_TABLE_SIZE 100000

// 해시 테이블의 노드 구조체
typedef struct ListNode {
    char data[MAX_ARRAY_SIZE];
    struct ListNode* next;
} ListNode;

// 해시 테이블 구조체
typedef struct HashTable {
    ListNode* table[HASH_TABLE_SIZE];
} HashTable;

void initializeHashTable(HashTable* ht);
int search(HashTable* ht, char data[]);
unsigned long hash(char str[]);
void insertNode(HashTable* ht, char data[]);
int isPrime(int num);

int only_one_count;   // 총 node의 수
int near_prime_count; // 1을 빼거나 더했을 때 소수인 정수의 수

int main() {

    //open file
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Unable to open file.");
        return 1;
    }

    HashTable ht;
    initializeHashTable(&ht);

    char buf[MAX_ARRAY_SIZE];

    while (fgets(buf, sizeof(buf), fp)) {
        buf[strcspn(buf, "\n")] = '\0'; // 개행문자 제거

        if (search(&ht, buf)) { // 중복되는 데이터를 제외하고 insert
            insertNode(&ht, buf);
        }
    }

    //close file
    fclose(fp);

    // 해시 테이블을 검사하면서 소수 개수를 계산
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ListNode* p = ht.table[i];

        while (p != NULL) {
            only_one_count++;

            // 문자열을 정수로 변환하여 계산
            char* ptr = strchr(p->data, '.');
            if (ptr != NULL) { // 소수점이 있고
                double double_data = atof(p->data);
                if (double_data - (int)double_data == 0.0) { // 소수점 아래의 숫자가 모두 0이면
                    // 1을 더하거나 빼도 소수인지 확인
                    long int_data = (long)double_data;
                    if (isPrime(int_data - 1) || isPrime(int_data + 1)) {
                        near_prime_count++;
                    }
                }
            } else { // 소수점이 없으면
                long int_data = atoi(p->data); // 문자열을 10진수로 변환
                if (isPrime(int_data - 1) || isPrime(int_data + 1)) {
                    near_prime_count++;
                }
            }

            p = p->next;
        }
    }

    printf("Only one count : %d\n", only_one_count);
    printf("Near prime count : %d", near_prime_count);

    // 해시 테이블의 메모리 해제
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ListNode* p = ht.table[i];
        
        while (p != NULL) {
            ListNode* temp = p;
            p = p->next;
            free(temp);
        }
    }

    return 0;
}

// 해시 테이블 초기화
void initializeHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 중복되는 문자열을 검색하는 함수
int search(HashTable* ht, char data[]) {
    unsigned long index = hash(data);

    ListNode* p = ht->table[index];

    while (p != NULL) {
        if (strcmp(p->data, data) == 0) {
            return 0; // 데이터가 이미 존재
        }
        p = p->next;
    }
    return 1; // 데이터가 존재하지 않음
}

// 해시 함수
unsigned long hash(char str[]) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % HASH_TABLE_SIZE;
}

// 연결리스트의 노드를 삽입하는 함수
void insertNode(HashTable* ht, char data[]) {
    unsigned long index = hash(data);

    // 새로운 노드 생성
    ListNode* Node = (ListNode*)malloc(sizeof(ListNode));
    
    strcpy(Node->data, data); // 문자열 복사
    Node->next = ht->table[index];
    ht->table[index] = Node;
}

// 소수를 판별하는 함수
int isPrime(int num) {
    if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }

    return 1;
}