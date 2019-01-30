// Billy Kwong
// bqkwong
// PA4
// Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

struct GraphObj {
	List *adj;
	int *col;
	int *par;
	int *dist;
	int order;
	int size;
	int source;
}GraphObj;

// Constructors-Destructors

// newGraph()
// Returns a pointer to a new GraphObj
Graph newGraph(int n) {
	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = calloc(n + 1, sizeof(List));
	G->col = calloc(n + 1, sizeof(int));
	G->par = calloc(n + 1, sizeof(int));
	G->dist = calloc(n + 1, sizeof(int));
	G->source = NIL;
	G->order = n;
	G->size = 0;
	for(int i = 0; i < (n + 1); ++i) {
		G->adj[i] = newList();
		G->col[i] = WHITE;
		G->par[i] = NIL;
		G->dist[i] = INF;
	}
	return G;
}

// freeGraph()
// Frees memory allocate to a GraphObj
void freeGraph(Graph *pG) {
	Graph pre = *pG;
	for(int i = 0; i < (pre->order + 1); ++i) {
		freeList(&(pre->adj[i]));
	}
	free(pre->adj);
	free(pre->par);
	free(pre->dist);
	free(pre->col);
	free(*pG);
	*pG = NULL;
}

// Access functions

// Returns the number of verticies in the Graph
int getOrder(Graph G) {
	return G->order;
}

// Returns the number of edges in the Graph
int getSize(Graph G) {
	return G->size;
}

// Returns the source from calling BFS(G, s)
int getSource(Graph G) {
	return G->source;
}

// Returns the par of a given vertex
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getParent() with vertex out of bounds\n");
		exit(1); 
	}
	return G->par[u];
}

// Returns the dist from the source to a given vertex
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
	if(getSource(G) == NIL) {
		return INF;
	}
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() with vertex out of bounds\n");
		exit(1); 
	}
	return G->dist[u];
}

// Returns the path from the source to given vertex
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {
	if(getSource(G) == NIL) {
		printf("Graph Error: calling getPath() with NULL source\n"); 
	}
	if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getPath() with vertex out of bounds\n");
		exit(1); 
	}
	int s = G->source;
	if(u == s) {
		prepend(L, s);
	} else if(G->par[u] == NIL) {
		append(L, NIL);
	} else {
		prepend(L, u);
		getPath(L, G, G->par[u]);
	}
}

// Manipulation procedures
 
// Clears all adjacency Lists for the Graph
void makeNull(Graph G) {
	for(int i = 0; i < (G->order + 1); ++i) {
		clear(G->adj[i]);
	}
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

// Adds a directed edge to the Graph G from u to v
// Pre: 1 <= u <= getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v) {
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
		printf("Graph Error: calling addArc() with verticies out of bounds\n");
		exit(1); 
	}
	List S = G->adj[u];
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

// Performs Breadth-first search on the Graph G with the
// given source vertex s.
void BFS(Graph G, int s) {
	for(int i = 0; i < (G->order + 1); ++i) {
		G->par[i] = NIL;
		G->dist[i] = INF;
		G->col[i] = WHITE;
	}
	G->source = s;
	G->dist[s] = 0;
	G->col[s] = GRAY;
	List Q = newList();
	prepend(Q, s);
	while(length(Q) > 0) {
		int ele = back(Q);
		deleteBack(Q);
		List adj = G->adj[ele];
		moveFront(adj);
		while(index(adj) > -1) {
			int v = get(adj);
			if(G->col[v] == WHITE) {
				G->col[v] = GRAY;
				G->par[v] = ele;
				G->dist[v] = G->dist[ele] + 1;
				prepend(Q, v);
			}
			moveNext(adj);
		}
	}
	freeList(&Q); 
}

// Prints out the Graph by iterating over and printing out
// each adjacency list with the row number preceeding it.
void printGraph(FILE *out, Graph G) {
	if(out == NULL || G == NULL) {
		printf("Graph Error: called printGraph() on a null reference");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); ++i) {
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}