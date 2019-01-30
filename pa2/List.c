// Billy Kwong
// bqkwong
// List.c

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs----------------------------------------------

//private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} 	NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
}   ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data, Node prev, Node next) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->prev = prev;
	N->next = next;
	return(N);
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
	if(pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL) {
	if(pL != NULL && *pL != NULL) { 
		Node tmp = (*pL)->front; 
		while(tmp != NULL) {
			Node cur = tmp;
			tmp = tmp->next;
			free(cur);
		}
		free(*pL);
		*pL = NULL;
	}
}

//Acess functions----------------------------------------------------------

// Returns the number of elements in this List.
int length(List L) {
	if(L == NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return L->length;
}	

// If cursor is defined, returns the index of the cursor
// element, otherwise returns -1.
int index(List L) {
	if(L == NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return L->index;
}	

// Returns front element.
// Pre: length() > 0
int front(List L) {
	if(L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: calling front() on empty List reference\n");
		exit(1);
	}
	return L->front->data;
}

// Returns back element.
// Pre: length() > 0
int back(List L) {
	if(L == NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: calling back() on empty List reference\n");
		exit(1);
	}
	return L->back->data;
}

// Returns cursor element.
// Pre: length() > 0
int get(List L) {
	if(L == NULL) {
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: calling get() with an undefined index on List\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: calling get() on empty List reference\n");
		exit(1);
	}
	return L->cursor->data;
}

// Returns true if this List A is identical to List B
int equals(List A, List B) {
	if(A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
	}
	if(A->length != B->length) {
		return 0;
	}
	Node N = B->front;
	Node M = A->front;
	while(N->next != NULL && M->next != NULL) {
		if(N->data != M->data)
			return 0;
		N = N->next;
		M = M->next;
	}
	return 1;
}

// Resets this List to empty state.
void clear(List L) {
	if(L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
	}
	Node tmp = L->front; 
	while(tmp != NULL) {
		Node cur = tmp;
		tmp = tmp->next;
		free(cur);
	}
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

// If List is non-empty, places the cursor under the front
// element, otherwise does nothing.
void moveFront(List L) {
	if(L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

// If List is non-empty, places the cursor under the back
// element, otherwise does nothing.
void moveBack(List L) {
	if(L == NULL) {
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
	}
	if(L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// If cursor is defined and not at front, moves cursor one step
// toward the front of this List, if cursor is defined and at front,
// cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L) {
	if(L == NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
	}
	if(  L->length < 1 ){
		printf("List Error: calling moveTo() on an empty List\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index != 0) {
		L->cursor = L->cursor->prev;
		--L->index;
	}
	else if(L->cursor != NULL && L->index == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, moves cursor one step
// toward the back of this List, if cursor is defined and at back,
// cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L) {
	if(L == NULL) {
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
	}
	if(  L->length < 1 ){
		printf("List Error: calling moveTo() on an empty List\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index != L->length - 1) {
		L->cursor = L->cursor->next;
		++L->index;
	}
	else if(L->cursor != NULL && L->index == L->length - 1) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before the front element.
void prepend(List L, int data) {
	if(L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data, NULL, L->front);
	if(L->front == NULL)
		L->back = N;
	else
		L->front->prev = N;
		L->front = N;
		++L->length;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
	if(L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
	}
	Node N = newNode(data, L->back, NULL);
	if(L->front == NULL)
		L->front = N;
	else
		L->back->next = N;
	L->back = N;
	++L->length;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data) {
	if(L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: insertBefore() called with an undefined index on List");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: insertBefore() called on an empty List");
		exit(1);
	}
	Node N = newNode(data, L->cursor->prev, L->cursor);
	if(L->cursor->prev != NULL)
		L->cursor->prev->next = N;
	else
		L->front = N;
	L->cursor->prev = N;
	++L->length;
}

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data) {
	if(L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
	}	
	if(L->index < 0) {
		printf("List Error: insertAfter() called with an undefined index on List");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: insertAfter() called on an empty List");
		exit(1);
	}
	Node N = newNode(data, L->cursor, L->cursor->next);
	if(L->cursor->next != NULL)
		L->cursor->next->prev = N;
	else
		L->back = N;
	L->cursor->next = N;
	++L->length;
}

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L) {
	if(L == NULL) {
		printf("List Error: deleteFront() called on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: deleteFront() called on an empty List\n"); 
		exit(1);
	}
	if(L->cursor == L->front) {
		L->cursor = NULL;
		L->index = -1;
	}
	Node tmp = L->front;
	L->front = L->front->next;
	L->front->prev = NULL;
	--L->length;
	freeNode(&tmp);
}

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L) {
	if(L == NULL) {
		printf("List Error: deleteBack() called on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: deleteBack() called on an empty List\n");
		exit(1);
	}
	if(L->cursor == L->back) {
		L->cursor = NULL;
		--L->index;
	}
	Node tmp = L->back;
	L->back = L->back->prev;
	L->back->next = NULL;
	--L->length;
	freeNode(&tmp);
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L) {
	if(L == NULL) {
		printf("List Error: delete() called on NULL List reference\n");
		exit(1);
	}
	if(L->length < 1) {
		printf("List Error: delete() called with an undefined index on List\n");
		exit(1);
	}
	if(L->index < 0) {
		printf("List Error: delete() called on empty List");
		exit(1);
	}
	if(L->cursor == L->back) {
		deleteBack(L);
	} else if(L->cursor == L->front) {
		deleteFront(L);
	} else {
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&N);
		L->cursor = NULL;
		L->index = -1;
		--L->length;
	}
}

// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
	Node N = L->front;
	while(N != NULL) {
		printf("%d ", N->data);
		N = N->next;
	}
}

// Returns a new List representing the same integer sequence as this
// List. The curor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
	List copy = newList();
	Node N = L->front;
	while(N != NULL) {
		append(copy, N->data);
		N = N->next;
	}
	return copy;
}