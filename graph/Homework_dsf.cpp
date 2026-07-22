#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 200
//그래프 구현
typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int vertex_total;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType* g,int* p) {
	g->vertex_total = 0;
	for (int i=0;i<MAX_VERTICES;i++){
		g->adj_list[i] = NULL;
		p[i] = 0;
	}
}

void insert_vertex(GraphType* g) {
	g->vertex_total++;
}

void insert_edge(GraphType*		g, int i, int j) {
	GraphNode* n = (GraphNode*)malloc(sizeof(GraphNode));
	n->vertex = j;
	n->link = g->adj_list[i];
	g->adj_list[i] = n;
}

int visit[MAX_VERTICES];

//dfs 구현
void dfs(GraphType*g,int u) {
	visit[u] = 1;
	printf("%d -> ", u);
	GraphNode* temp = g->adj_list[u];
	for (GraphNode* i = temp;i != NULL;i = i->link) {
		if (visit[i->vertex] != 1) {
			dfs(g, i->vertex);
		}
	}
}

int main() {
	//그래프 구축
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g,visit);

	FILE* fp = fopen("searchgraph.txt", "r");
	int i, j, t=0, max = 0;

	while (fscanf(fp, "%d %d", &i, &j) != EOF) {
		insert_edge(g, i, j);
		insert_edge(g, j, i);
		if (i > max) max = i;
		if (j > max)  max = j;
	}
	g->vertex_total = max+1;
	fclose(fp);
	//dfs 실행

	dfs(g, 1);

	free(g);
	return 0;
}
