//스택버전

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 200

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int total_vertex;
	GraphNode* adj_list[MAX_SIZE];
};

typedef struct StackType {
	int top;
	int data[MAX_SIZE];
}StackType;
int visit[MAX_SIZE];

void init(GraphType* g,GraphType* g_T,StackType* s,int* p) {
	g->total_vertex = 0;
	g_T->total_vertex = 0;
	for (int i = 0;i < MAX_SIZE;i++) {
		g->adj_list[i] = NULL;
		g_T->adj_list[i] = NULL;
		p[i] = 0;
	}
	s->top = -1;
}
//그래프 구축
void insert_edge(GraphType* g, int i, int j) {
	GraphNode* temp = (GraphNode*)malloc(sizeof(GraphNode));
	temp->vertex = j;
	temp->link = g->adj_list[i];
	g->adj_list[i] = temp;
}
//스택 구축
void push(StackType* s,int i) {
	s->data[++s->top] = i;
}

int pop(StackType* s) {
	return s->data[s->top--];
}
//두번째 DFS(일반)
void dfs(GraphType* g,int i) {
	visit[i] = 1;
	printf("%d ->", i);
		for (GraphNode* temp = g->adj_list[i];temp;temp = temp->link) {
			if (visit[temp->vertex] != 1) {
				dfs(g, temp->vertex);
		}
	}
}
//첫번째 DFS
void dfs_ko(GraphType* g, StackType* s,int i) {
	if (visit[i] == 1) {
		printf("사이클 발생 -> %d", i);
	}
	if (visit[i] == 2) {
		return;
	}
	visit[i] = 1;
	for (GraphNode* temp = g->adj_list[i];temp;temp = temp->link) {
		dfs_ko(g, s, temp->vertex);
	}
	visit[i] = 2;
	push(s, i);
}

int main() {
	//변수 및 구조체 선언
	int n = 0, m = 0, u = 0, v = 0;
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	StackType* s = (StackType*)malloc(sizeof(StackType));
	GraphType* g_T= (GraphType*)malloc(sizeof(GraphType));
	init(g,g_T,s,visit);

	//파일 들여오기
	FILE* df;
	int error = fopen_s(&df, "searchgraph.txt", "r");

	//그래프 구축
	fscanf_s(df, "%d %d", &n, &m);

	g->total_vertex = n;
	g_T->total_vertex = n;

	for(int i=1; i<=m;i++) {
		fscanf_s(df, "%d %d", &v, &u);
		insert_edge(g, v, u);
		insert_edge(g_T, u, v);
	}

	fclose(df);

	//1번째 DFS 실행 -> 스택에 마지막에 끝난 vertex를 push
	for (int k = 0;k < g->total_vertex;k++) {
		if (visit[k] == 0) {
			dfs_ko(g, s, k);
		}
	}

	//visit 초기화
	for (int i = 0;i < g->total_vertex;i++) {
		visit[i] = 0;
	}

	//stack을 기반으로 pop하면서 역순으로 DFS
	while (s->top != -1){
		int index = pop(s);
		if (visit[index] == 0) {
			printf("SCC 그룹: ");
			dfs(g_T, index);
		}
	}

	free(g);
	free(g_T);
	free(s);
	return 0;
}