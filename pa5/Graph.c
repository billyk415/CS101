// Billy Kwong
// bqkwong
// PA5
// Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#define WH 0
#define GR 1
#define BL 2

struct GraphObj {
	List *adjacent;
	int *color;
	int *parent;
	int *discover;
	int *finish;
	int order;
	int size;
};

/* Constructors-Destructors */

// newGraph()
// Returns a pointer to a new GraphObj
Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));
	G->adjacent = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));
	G->finish = calloc(n + 1, sizeof(int));
	G->order = n;
	G->size = 0;
	for(int i = 0; i < (n + 1); ++i) {
		G->adjacent[i] = newList();
		G->color[i] = WH;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	return G;
}

// freeGraph()
// Frees memory allocate to a GraphObj
void freeGraph(Graph *pG) {
	for (int i = 0; i <= getOrder(*pG); i++) {
			freeList(&(*pG)->adjacent[i]);
	}
	free((*pG)->adjacent);
	free((*pG)->color);
	free((*pG)->parent);
	free((*pG)->discover);
	free((*pG)->finish);
	free(*pG);
	*pG = NULL;
}

/* Access functions */

// Returns the number of verticies in the Graph
int getOrder(Graph G) {
	return G->order;
}

// Returns the number of edges in the Graph
int getSize(Graph G) {
	return G->size;
}

// Returns the par of a given vertex
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getParent() with vertex out of bounds\n");
		exit(1); 
	}
	return G->parent[u];
}

// Returns the discover time of a given vertex
// Pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDiscover() with vertex out of bounds\n");
		exit(1); 
	}
	return G->discover[u];
}

// Returns the finish time of a given vertex
// Pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getFinish() with vertex out of bounds\n");
		exit(1); 
	}
	return G->finish[u];
}

/* Manipulation procedures */

// Adds a directed edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addArc() with verticies out of bounds\n");
		exit(1); 
	}
	List S = G->adjacent[u];
	moveFront(S);
	while(index(S) > -1 && v > get(S)) {
		moveNext(S);
	}
	if(index(S) == -1)
		append(S, v);
	else 
		insertBefore(S, v);
	G->size++;
}

// Adds an undirected edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v) {
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addEdge() with verticies out of bounds\n");
		exit(1); 
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}


// Recursive part of DFS that hits all vertices
// on a vertex's adjacent list.
void Visit(Graph G, List S, int u, int *time) {
	G->color[u] = GR;
	G->discover[u] = ++*time;
	moveFront(G->adjacent[u]);
	while(index(G->adjacent[u]) >= 0) {
		int v = get(G->adjacent[u]);
		if(G->color[v] == WH) {
			G->parent[v] = u;
			Visit(G, S, v, time);
		}
		moveNext(G->adjacent[u]);
	}
	G->color[u] = BL;
	G->finish[u] = ++*time;
	prepend(S, u);
}

// Performs Depth-first search with the vertices in the order
// of List S.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
	if(length(S) != getOrder(G)) {
		printf("Graph Error: called DFS() without matching sizes\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); ++i) {
		G->color[i] = WH;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	int time = 0;
	moveFront(S);
	while(index(S) >= 0) {
		int u = get(S);
		if(G->color[u] == WH) {
			Visit(G, S, u, &time);   
		}
		moveNext(S);
	}

	for(int size = length(S)/2; size > 0; --size) {
		deleteBack(S);
	}
}

/* Other Functions */

// Returns the transpose of a given Graph
Graph transpose(Graph G) {
	if (G == NULL) {
			printf("transpose() Error: calling transpose() on NULL graph\n");
			exit(1);
	}

	Graph T = newGraph(getOrder(G));

	for (int i = 1; i<= getOrder(G); i++) {
		moveFront(G->adjacent[i]);
		while (index(G->adjacent[i]) >= 0) {
			addArc(T, get(G->adjacent[i]), i);
			moveNext(G->adjacent[i]);
		}
	}
	return T;
}

// Returns a copy of a given Graph
Graph copyGraph (Graph G) {
	if (G == NULL) {
		printf("copyGraph() Error: calling copyGraph() on NULL graph\n");
		exit(1);
	}

	Graph C = newGraph(getOrder(G));

	for (int i = 1; i<= getOrder(G); i++) {
		moveFront(G->adjacent[i]);
		while (index(G->adjacent[i]) >= 0) {
			addArc(C, i, get(G->adjacent[i]));
			moveNext(G->adjacent[i]);
		}
	}
	return C;
}

// Prints out the Graph by iterating over and printing out
// each adjacency list with the row number preceeding it.
void printGraph(FILE* out, Graph G) {
	if (out == NULL) {
		printf("printGraph() Error: calling printGraph() on NULL file\n");
		exit(1);
	}
	if (G == NULL) {
		printf("printGraph() Error: calling printGraph() on NULL graph\n");
		exit(1);
	}

	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adjacent[i]);
		fprintf(out, "\n");
	}
}


