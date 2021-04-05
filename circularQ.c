/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4
#pragma warning(disable:4996)

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE]; //원소를 저장할 배열
	int front, rear; //front에서 자료 삭제, rear에서 자료 삽입
}QueueType;


QueueType* createQueue();
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();

int main(void)
{
	QueueType* cQ = createQueue(); //cQ라는 큐타입 자료형 변수 선언
	element data; //element형 data선언
	char command;
	printf("2020039071 조준화");
	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I': 
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType* createQueue() //큐를 만드는 함수
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ) //큐 free함수
{
	if (cQ == NULL) return 1; //이미 비어있으면 1 리턴
	free(cQ);
	return 1; //비어있지 않으면 free후 1 리턴
}

element getElement() //큐에 넣을 데이터 입력받는 함수
{
	element item; 
	printf("Input element = ");
	scanf(" %c", &item); 
	return item;
}


/* complete the function */
int isEmpty(QueueType* cQ) //큐가 비어있으면 1 리턴 아니면 0리턴
{
	if (cQ->front == cQ->rear) // front 와 rear가 같다면 큐가 비어있는 것이다
		return 1;
	else
		return 0;
}


/* complete the function */
int isFull(QueueType* cQ) //큐가 가득 차있으면 1 리턴 아니면 0리턴
{
	if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front % MAX_QUEUE_SIZE) // (rear+1)% MAXSIZE 와 front % MAXSIZE 가 같다면 큐가 가득 찬것이다
		return 1;
	else
		return 0;
}


void enQueue(QueueType* cQ, element item) //큐에 데이터 삽입
{
	cQ->rear = (cQ->rear) % MAX_QUEUE_SIZE; //cQ -> rear 에 MAX_QUEUE_SIZE를 모들러 연산해서 나온 값을 저장
	if (isFull(cQ))
		printf("Circular Queue is full!"); //큐가 가득 차있다면 그냥 종료
	else
		cQ->queue[cQ->rear++] = item; //아니라면 rear가 가리키는 곳에 item할당 후 rear++
}


void deQueue(QueueType* cQ, element* item)
{
	cQ->front = (cQ->front) % MAX_QUEUE_SIZE; // /cQ -> front 에 MAX_QUEUE_SIZE를 모들러 연산해서 나온 값을 저장
	if (isEmpty(cQ))
		printf("Circular Queue is already empty!"); //큐가 이미 비어있다면 그냥 종료
	else
		cQ->front++; //아니라면 fornt ++ 해서 front 부분의 원소를 삭제한것과 동일하게 취급
}


void printQ(QueueType* cQ) //Q 프린트함수
{
	int i, first, last;

	first = (cQ->front ) % MAX_QUEUE_SIZE; //front부터 rear까지 출력
	last = (cQ->rear ) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ) //디버그
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //큐에 저장된 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


