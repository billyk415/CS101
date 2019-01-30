// Billy Kwong
// bqkwong
// PA4
// List.c
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs----------------------------------------------------------------------

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
	int index;
	int length;
}   ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

// newList()
// Returns reference to new empty List object.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return (L);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
		free(*pN); 
		*pN = NULL;
    }
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List *pL) {
    if (pL == NULL || *pL == NULL) {
		return;
    }
    while (length(*pL) != 0) {
		deleteFront(*pL);
    }
    free(*pL); 
    *pL = NULL;
}

// Access functions -------------------------------------------------------------------

// Returns 0(false) if List is not empty, 1 if true
int isEmpty(List L) {
    if (L == NULL) {
		printf("List Error: calling isEmpty() on NULL List reference\n");
		exit(1);
    }
    return (L->length == 0);
}

// Returns the number of elements in this List
int length(List L) {
    if (L == NULL) {
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
    }
    return (L->length);
}

// If cursor is defined, returns the index of the cursor element,
// otherwise returns -1.
int index(List L) {
    Node N = L->front;
    if (L == NULL) {
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
    }
    int i = 0;
    while (i != length(L) && N != NULL) {
		if (N == L->cursor) return i;
		else {
			i++;
			N = N->next;
		}
    }
    return -1;
}

// Returns front element. Pre: length()>0
int front(List L) {
    if (L == NULL) {
		printf("List Error: calling front() on NULL List reference\n");
		exit(1);
    }
    if (L->length < 1) {
		printf("List Error: calling front() on an empty List\n");
		exit(1);
    }
    return (L->front->data);
}

// Returns back element. Pre: length()>0
int back(List L) {
    if (L == NULL) {
		printf("List Error: calling back() on NULL List reference\n");
		exit(1);
    }
    if (L->length < 1) {
		printf("List Error: calling back() on an empty List\n");
		exit(1);
    }
    return (L->back->data);
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
    }
    if (isEmpty(L) || index(L) < 0) {
		printf("List Error: calling get() on empty List\n");
		exit(1);
    }
    return (L->cursor->data);
}

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists. 
int equals(List A, List B) {
    int eq = 1;
    Node N = NULL;
    Node M = NULL;
    if (A == NULL || B == NULL) {
		printf("List Error: calling equals() on NULL List reference\n");
		exit(1);
    }
    N = A->front;
    M = B->front;
    if (length(A) == length(B)) {
		while (eq && N != NULL) {
			eq = (N->data == M->data);
			N = N->next;
			M = M->next;
		}
		return eq;
    }
    return 0;
}

// Manipulation Procedures -------------------------------------------------
   
// Resets this List to its original empty state.
void clear(List L) {
    if (L == NULL) {
		printf("List Error: calling clear() on NULL List reference\n");
		exit(1);
    }
    if (isEmpty(L)) {
		return; 
    }
    while (L->front != NULL) {
		deleteFront(L);
    }
}

// If List is non-empty, places the cursor under the front
// element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(1);
    }
    if (length(L) > 0) {
		L->cursor = L->front;
    }
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(1);
    }
    if (length(L) > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
    }
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L) {
    if (L == NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(1);
    }
    if (0 < index(L) && index(L) <= length(L) - 1) {
		L->cursor = L->cursor->prev;
		--L->index;
    }
    else if (index(L) == 0 || index(L) == -1) {
		L->cursor = NULL;
		L->index = -1;
    }
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L) {
    if (L == NULL) {
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(1);
    }
    if (0 <= index(L) && index(L) < length(L) - 1) {
		L->cursor = L->cursor->next;
		++L->index;
    }
    else if (index(L) == length(L) - 1) {
		L->cursor = NULL;
		L->index = -1;
    }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data) {
    if (L == NULL) {
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(1);
    }
    Node N = newNode(data);
    if (length(L) == 0) {
		L->front = L->back = N;
    }
    else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
    }
    ++L->length;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data) {
    if (L == NULL) {
		printf("List Error: calling append() on NULL List reference\n");
		exit(1);
    }
    Node N = newNode(data);
    if (length(L) == 0) {
		L->front = L->back = N;
    } 
    else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
    }
    ++L->length;
}

// Inserts new element before cursor element in this
// List. Pre: length()>0, getIndex()>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(1);
    }
    if ( isEmpty(L) || index(L) < 0) {
		printf("List Error: calling insertBefore() on empty List\n");
		exit(1);
    }
    Node N = newNode(data);
    if (L->cursor == L->front) {
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
    }
    else {
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		N->next = L->cursor;
		L->cursor->prev = N;
    }
    ++L->length;
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data) {
    if (L == NULL) {
		printf("List Error: calling insertAfter() on NULL List reference\n");
		exit(1);
    }
    if (isEmpty(L) || index(L) < 0) {
		printf("List Error: calling insertAfter() on empty List\n");
		exit(1);
    }
    Node N = newNode(data);
    if (L->cursor == L->back) {
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
    }
    else {
		N->prev = L->cursor;
		N->next = L->cursor->next;
		L->cursor->next->prev = N;
		L->cursor->next = N;
    }
    ++L->length;
}

// Deletes the front element. Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(1);
    }
    if (isEmpty(L)) {
		printf("List Error: Using: deleteFront() to move cursor off List\n");
		exit(1);
    }
    Node N = L->front;
    if (length(L) > 1) {
		L->front = L->front->next;
		L->front->prev = NULL;
    } 
    else {
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
    }
    --L->length;
    freeNode(&N);
}

// Deletes the back element. Pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(1);
    }
    if (isEmpty(L)) {
		printf("List Error: calling deleteBack() on empty List\n");
		exit(1);
    }
    Node N = L->back;
    if (length(L) > 1) {
		L->back = L->back->prev;
		L->back->next = NULL;
    }
    else {
		L->front = L->back = L->cursor = NULL;
		L->index = -1;
    }
    --L->length;
    freeNode(&N);
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
		printf("List Error: calling delete() on NULL List reference\n");
		exit(1);
    }
    if ( isEmpty(L) || index(L) < 0) {
		printf("List Error: calling delete() on empty List\n");
		exit(1);
    }
    Node N = NULL;
    N = L->cursor;
    if (N==L->front)
		deleteFront(L);
    else if (N==L->back)
		deleteBack(L);
    else{
		L->cursor->prev->next = L->cursor->next;
		L->cursor->prev = L->cursor->next = NULL;
		freeNode(&N);
		L->cursor = NULL;
		L->index = -1;
		--L->length;
    }
}

// Other Functions ---------------------------------------------------------

// prints the List
void printList(FILE *out, List L) {
    if (L == NULL) {
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
    }
  
    for (Node N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%d ", N->data);
    }
}

// copy()
// Returns a new List identical to this List.
List copyList(List L) {
    List c = newList();
	Node tmp = L->front;
	while(tmp != NULL) {
		append(c, tmp->data);
		tmp = tmp->next;
	}
	return c;
}