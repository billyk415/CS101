// Billy Kwong
// bqkwong
// PA5
// FindComponents.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char *argv[]) {
	FILE *in;
	FILE *out;
	int component = 1;
	int scc = 0;
	int i,n,u,v,order;
	Graph G = NULL;
	Graph T = NULL;
	List S = newList();
	List SCC = newList();
   
	// check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
  
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if (out == NULL) {
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
 
	fscanf(in, "%d", &order);
	G = newGraph(order);

	while (fscanf(in, "%d %d", &u, &v) == 2) { 
		if (u == 0 && v == 0) break;
		addArc(G, u, v);
	}


	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G); 
	for (i = 1; i <= getOrder(G); i++) append(S, i);

	DFS(G, S);
   
	T = transpose(G);
	DFS(T, S);

  
	for (moveFront(S); index(S) != -1; moveNext(S)) {  
		if (getParent(T, get(S)) == NIL) {
		scc++;
		}
	}
 
	fprintf(out,"\nG contains %d strongly connected components:\n", scc);
 
  
	moveBack(S);
	while (index(S) != -1) { 
		n = get(S);
		prepend(SCC, n);
		if (getParent(T, n) == NIL) {
			fprintf(out,"Component %d: ", component);
			printList(out, SCC);
		fprintf(out,"\n");
		clear(SCC);
		component++;
		}
		movePrev(S);
	}
	
	//close files
	fclose(in);
	fclose(out);
     
	freeGraph(&G);
	freeGraph(&T);
	freeList(&S);
	freeList(&SCC);
}	
	