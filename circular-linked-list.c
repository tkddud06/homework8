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
/* �ʿ��� ������� �߰� */

typedef struct Node { // ��带 ��Ÿ���� ����ü
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
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

	do{ // �Է¹޴� ���ڿ� ����, �� ��ɵ��� �����ϰ�, q�� ������ �����Ѵ�.
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	listNode* prev = NULL;
	listNode* ptr = h->rlink;
	
	while(ptr != h) // ��� ��带 �� ���� ���� ���ƿö����� ����
	{
		prev = ptr; // ptr�� ���� ���� ptr�� ���ܿ���,
		ptr = ptr->rlink; // ptr�� ���� ���� �̵���Ų ��,
		free(prev); // ��� ������ ptr�̿��� prev�� free�Ѵ�.
	}
	
	free(h); // ����� free�Ѵ�
	
	return 0;
}



void printList(listNode* h) { // ��ŧ�� ���� ��ũ�� ����Ʈ�� ����Ѵ�
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // �ʱ�ȭ�� �� �Ǿ��� ��
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) { // ��ü�� ���鼭 ���(����� �ٽ� ������ ����)
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i); // ī��Ʈ�� ������ ����


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // ����� �ּ� ���� ���

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) { // ��ü�� ���鼭 �� ����� �ּ� ���� ���
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	if(h->rlink == h) // ����Ʈ�� �� ���
	{
		insertFirst(h, key); // ù��°�� �ִ� �Լ��� ����
		return 0;
	}
	
	// �Ϲ����� ���
	
	listNode* prev = h->llink;  // ������ ��ġ(�ǳ�����, ��� ����)�� ���, �� ���� ������ ����� ���� ��尡 �� ��带 prev�� ����
	prev->rlink = (listNode*)malloc(sizeof(listNode)); // prev�� ���� ��忡 �� ��� �����Ҵ�
	prev->rlink->key = key; // Ű ����
	prev->rlink->llink = prev; // �� ����� llink�� prev�� ����
	prev->rlink->rlink = h; // �� ����� rlink�� h�� ����
	h->llink = prev->rlink; // h�� llink�� �� ��忡 ����
	

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	if(h->rlink == h) // �� ����Ʈ�� ���
	{
		printf("�� ����Ʈ�� ������ �� �����ϴ�.");
		return 1;
	}

	listNode* del = h->llink; // ������ ���, �� h�� llink�� ������ ��带 del�� ����
	del->llink->rlink = h; // ���� ����� ���� ����� rlink�� ���� ����� ������ ����� h�� ����
	h->llink = del->llink; // ���� ����� ������ ���, �� h�� llink�� ���� ����� ���� ��忡 ����
	free(del); // ���� ��� free
	
	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	
	if(h->rlink == h) // ����Ʈ�� �� ���¶��
	{
		listNode* newnode = (listNode*)malloc(sizeof(listNode)); // �� ��� �����Ҵ�
		h->rlink = newnode; // ����� h�� llink�� rlink�� ��� �� ��忡 �̾��ش�
		h->llink = newnode;
		newnode->rlink = h; // �� ����� llink�� rlink�� ��� ����� h�� �̾��ش�
		newnode->llink = h;
		newnode->key = key; // Ű ����
		return 0;
	}
	

	// �Ϲ����� ���
	listNode* next = h->rlink; // ������ ��� ��ġ, �� h�� rlink�� ��带 next�� ����. next�� ���ο� ����� ���� ��尡 �� ����.
	h->rlink = (listNode*)malloc(sizeof(listNode)); // h�� rlink�� �� ��� �����Ҵ�
	h->rlink->key = key; // Ű ����
	h->rlink->rlink = next; // ���ο� ����� rllink�� next�� ����
	h->rlink->llink = h; // ���ο� ����� llink�� ���, �� h�� ����
	next->llink = h->rlink; // ���ο� ����� ���� ����� next�� link�� �� ��� ����
	
	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	
	if(h->rlink == h) // ����Ʈ�� �� ���¶��
	{
		printf("�� ����Ʈ�� ������ �� �����ϴ�.");
		return 1;
	}

	// �Ϲ����� ���

	listNode* del = h->rlink; // ������ ���, �� h�� rlink�� ù��° ��带 del�� ����
	del->rlink->llink = h; // ���� ����� ���� ����� llink�� �ڽ��� ���� ����� ���, �� h�� ����
	h->rlink = del->rlink; // ���� ����� ���� ����� ���, �� h�� rlink�� �ڽ��� ���� ���� ����
	free(del); // ������ ��� free
	
	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
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

	}while (ptr != h); // ������� ������ ��� ������ llink�� rlink�� ���� �ٲ��־���ϹǷ�, do-while�� ���. 
	// ptr�� prev�� ���� ���� ���(rlink)�� �ּҸ� �����ϴ� ������ �ϰ�, ���������� ���� �ٲ�°��� prev�� rlink�� llink.
	// ���ʷ� �Ѿ�鼭, ����� ������ ��� ����� rlink�� llink�� �ѹ��� �ٲپ���

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	
	if(h->rlink == h) // �� ����Ʈ�� ���
	{
		insertFirst(h, key);
		return 0;
	}
	
	// �Ϲ����� ���
	
	listNode* next = h->rlink; // ���Ե� ����� ���� ��带 ǥ���ϴ� next ����
	
	while(next->key <= key) // �Է¹��� key���� ū���� ���� ������ �ݺ�
	{
		next = next->rlink; // ���� ���� �̵�
		if(next == h) // ������ ���������� �Է¹��� key���� ū���� ������ ��带 ã�� ���� ��� (�ݺ����� ��������, �������� ��尡 ���ԵǴ� ���°� ��.)
		{
			break;
		}
	}
	
	listNode* prev = next->llink; // ���Ե� ����� ���� ��带 ǥ���ϴ� prev ����
	prev->rlink = (listNode*)malloc(sizeof(listNode)); // prev�� rlink�� �� ��� �����Ҵ�
	prev->rlink->key = key; // Ű ����
	next->llink = prev->rlink; // next�� llink�� �� ��� ����
	prev->rlink->llink = prev; // �� ����� llink�� ���� ���(prev) ����
	prev->rlink->rlink = next; // �� ����� rlink�� ���� ���(next) ����
	
	
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	
	if(h->rlink == h) // �� ����Ʈ�� ���
	{
		printf("�� ����Ʈ�� ������ �� �����ϴ�.");
		return 1;
	}

	listNode* del = h->rlink; // ���� ��带 ǥ���ϴ� del ����
	while(del->key != key) // �ش� Ű�� ã�������� �ݺ�
	{
		del = del->rlink; // ���� ���� �̵�
		if(del == h) // ���� ������ �� ���������� ã�� ���ߴٸ�
		{
			printf("�ش� Ű�� ���� ��带 ã�� ���߽��ϴ�.");
			return 1;
		}
	}
	
	del->rlink->llink = del->llink; // ���� ����� ���� ����� llink�� ���� ����� ���� ���� ����
	del->llink->rlink = del->rlink; // ���� ����� ���� ����� rrlink�� ���� ����� ���� ���� ����
	free(del); // ���� ��� free
	
	return 0;
}


