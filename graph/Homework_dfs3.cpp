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

void init(GraphType* g, int* p) {
	g->vertex_total = 0;
	for (int i = 0;i < MAX_VERTICES;i++) {
		g->adj_list[i] = NULL;
		p[i] = 0;
	}
}

void insert_vertex(GraphType* g) {
	g->vertex_total++;
}

void insert_edge(GraphType* g, int i, int j) {
	GraphNode* n = (GraphNode*)malloc(sizeof(GraphNode));
	n->vertex = j;
	n->link = g->adj_list[i];
	g->adj_list[i] = n;
}

void print_adj_list(GraphType* g) {
	for (int i = 1;i < MAX_VERTICES;i++) {
		printf("정점 %d의 인접 리스트", i);
		GraphNode* temp = g->adj_list[i];
		while (temp != NULL) {
			printf("-> %d", temp->vertex);
			temp = temp->link;
		}
		printf("\n");
	}
}
//스택, DFS구현
typedef struct stack {
	int top;
	int data[MAX_VERTICES];
}Stack;

void init_Stack(Stack* s) {
	s->top = -1;
}

int is_empty(Stack* s) {
	return s->top == -1;
}

int is_full(Stack* s) {
	return s->top == MAX_VERTICES - 1;
}

void push(Stack* s, int data) {
	s->data[++(s->top)] = data;
}

int pop(Stack* s) {
	return s->data[(s->top)--];
}

int visit[MAX_VERTICES];
void dfs(GraphType* g, int u) {
	Stack s;
	init_Stack(&s);
	push(&s, u);
	while (!is_empty(&s)) {
		u = pop(&s);
		if (visit[u] == 1) {
			continue;
		}
		visit[u] = 1;
		printf("%d -> ", u);
		for (GraphNode* p = g->adj_list[u];p;p = p->link) {
			if (!visit[p->vertex]) {
				push(&s, p->vertex);
			}
		}
	}
}

int main() {
	//그래프 구축
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	init(g, visit);

	FILE* fp = fopen("C:\\Users\\USER\\Desktop\\searchgraph.txt", "r");
	int i, j, t = 0, max = 0;

	while (fscanf(fp, "%d %d", &i, &j) != EOF) {
		insert_edge(g, i, j);
		insert_edge(g, j, i);
		if (i > max) max = i;
		if (j > max)  max = j;
	}
	g->vertex_total = max + 1;
	fclose(fp);
	//dfs 실행

	dfs(g, 1);

	free(g);
	return 0;
}
