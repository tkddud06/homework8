/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { // 노드를 나타내는 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{ // 입력받는 문자에 따라, 각 기능들을 수행하고, q를 받으면 종료한다.
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* prev = NULL;
	listNode* ptr = h->rlink;
	
	while(ptr != h) // 모든 노드를 다 돌고 헤드로 돌아올때까지 수행
	{
		prev = ptr; // ptr의 이전 노드는 ptr로 땡겨오고,
		ptr = ptr->rlink; // ptr은 다음 노드로 이동시킨 뒤,
		free(prev); // 방금 전까지 ptr이였던 prev를 free한다.
	}
	
	free(h); // 헤더를 free한다
	
	return 0;
}



void printList(listNode* h) { // 서큘러 더블리 링크드 리스트를 출력한다
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 초기화가 안 되었을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) { // 전체를 돌면서 출력(헤더를 다시 만나면 정지)
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i); // 카운트한 원소의 개수


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // 헤더의 주소 상태 출력

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { // 전체를 돌면서 각 노드의 주소 상태 출력
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	if(h->rlink == h) // 리스트가 빈 경우
	{
		insertFirst(h, key); // 첫번째에 넣는 함수로 연결
		return 0;
	}
	
	// 일반적인 경우
	
	listNode* prev = h->llink;  // 삽입할 위치(맨끝이자, 헤드 직전)의 노드, 즉 새로 삽입할 노드의 이전 노드가 될 노드를 prev로 지정
	prev->rlink = (listNode*)malloc(sizeof(listNode)); // prev의 다음 노드에 새 노드 동적할당
	prev->rlink->key = key; // 키 삽입
	prev->rlink->llink = prev; // 새 노드의 llink를 prev에 연결
	prev->rlink->rlink = h; // 새 노드의 rlink를 h에 연결
	h->llink = prev->rlink; // h의 llink를 새 노드에 연결
	

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	if(h->rlink == h) // 빈 리스트인 경우
	{
		printf("빈 리스트라 삭제할 수 없습니다.");
		return 1;
	}

	listNode* del = h->llink; // 제거할 노드, 즉 h의 llink인 마지막 노드를 del로 지정
	del->llink->rlink = h; // 지울 노드의 왼쪽 노드의 rlink를 지울 노드의 오른쪽 노드인 h에 연결
	h->llink = del->llink; // 지울 노드의 오른쪽 노드, 즉 h의 llink를 지울 노드의 왼쪽 노드에 연결
	free(del); // 지울 노드 free
	
	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	
	if(h->rlink == h) // 리스트가 빈 상태라면
	{
		listNode* newnode = (listNode*)malloc(sizeof(listNode)); // 새 노드 동적할당
		h->rlink = newnode; // 헤더인 h의 llink와 rlink를 모두 새 노드에 이어준다
		h->llink = newnode;
		newnode->rlink = h; // 새 노드의 llink와 rlink를 모두 헤더인 h에 이어준다
		newnode->llink = h;
		newnode->key = key; // 키 삽입
		return 0;
	}
	

	// 일반적인 경우
	listNode* next = h->rlink; // 삽입할 노드 위치, 즉 h의 rlink인 노드를 next로 지정. next는 새로운 노드의 다음 노드가 될 것임.
	h->rlink = (listNode*)malloc(sizeof(listNode)); // h의 rlink에 새 노드 동적할당
	h->rlink->key = key; // 키 삽입
	h->rlink->rlink = next; // 새로운 노드의 rllink에 next를 연결
	h->rlink->llink = h; // 새로운 노드의 llink에 헤더, 즉 h를 연결
	next->llink = h->rlink; // 새로운 노드의 다음 노드인 next의 link에 새 노드 연결
	
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	
	if(h->rlink == h) // 리스트가 빈 상태라면
	{
		printf("빈 리스트라 삭제할 수 없습니다.");
		return 1;
	}

	// 일반적인 경우

	listNode* del = h->rlink; // 제거할 노드, 즉 h의 rlink인 첫번째 노드를 del로 지정
	del->rlink->llink = h; // 지울 노드의 다음 노드의 llink를 자신의 왼쪽 노드인 헤더, 즉 h로 연결
	h->rlink = del->rlink; // 지울 노드의 왼쪽 노드인 헤더, 즉 h의 rlink를 자신의 다음 노드로 연결
	free(del); // 제거할 노드 free
	
	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	listNode* prev = NULL;
	listNode* ptr = h;
	
	do
	{
		prev = ptr;
		ptr = ptr->rlink;
		prev->rlink = prev->llink;
		prev->llink = ptr;

	}while (ptr != h); // 헤더부터 끝까지 모든 노드들의 llink와 rlink를 서로 바꿔주어야하므로, do-while문 사용. 
	// ptr이 prev의 기존 다음 노드(rlink)의 주소를 저장하는 역할을 하고, 실질적으로 값이 바뀌는것은 prev의 rlink와 llink.
	// 차례로 넘어가면서, 헤더를 포함한 모든 노드의 rlink와 llink를 한번씩 바꾸어줌

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	
	if(h->rlink == h) // 빈 리스트인 경우
	{
		insertFirst(h, key);
		return 0;
	}
	
	// 일반적인 경우
	
	listNode* next = h->rlink; // 삽입될 노드의 다음 노드를 표시하는 next 선언
	
	while(next->key <= key) // 입력받은 key보다 큰값이 나올 때까지 반복
	{
		next = next->rlink; // 다음 노드로 이동
		if(next == h) // 끝까지 돌았음에도 입력받은 key보다 큰값이 나오는 노드를 찾지 못한 경우 (반복문을 빠져나와, 마지막에 노드가 삽입되는 형태가 됨.)
		{
			break;
		}
	}
	
	listNode* prev = next->llink; // 삽입될 노드의 이전 노드를 표시하는 prev 선언
	prev->rlink = (listNode*)malloc(sizeof(listNode)); // prev의 rlink에 새 노드 동적할당
	prev->rlink->key = key; // 키 삽입
	next->llink = prev->rlink; // next의 llink에 새 노드 연결
	prev->rlink->llink = prev; // 새 노드의 llink에 이전 노드(prev) 연결
	prev->rlink->rlink = next; // 새 노드의 rlink에 다음 노드(next) 연결
	
	
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	
	if(h->rlink == h) // 빈 리스트인 경우
	{
		printf("빈 리스트라 삭제할 수 없습니다.");
		return 1;
	}

	listNode* del = h->rlink; // 지울 노드를 표시하는 del 선언
	while(del->key != key) // 해당 키를 찾을때까지 반복
	{
		del = del->rlink; // 다음 노드로 이동
		if(del == h) // 만약 끝까지 다 돌았음에도 찾지 못했다면
		{
			printf("해당 키를 가진 노드를 찾지 못했습니다.");
			return 1;
		}
	}
	
	del->rlink->llink = del->llink; // 지울 노드의 다음 노드의 llink를 지울 노드의 이전 노드로 연결
	del->llink->rlink = del->rlink; // 지을 노드의 이전 노드의 rrlink를 지울 노드의 다음 노드로 연결
	free(del); // 지울 노드 free
	
	return 0;
}


