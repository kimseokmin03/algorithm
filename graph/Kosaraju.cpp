//수업내용

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

int n = 0, m = 0, v=0, u=0, clock = 1, ccflag=1;
vector<int> Graph[10001];
vector<int> Graph_T[10001];
bool visit[10001];
int cc[10001], pre[10001], post[10001];

void pre_T(int v) {
	pre[v] = clock++;
}

void post_T(int v) {
	post[v] = clock++;
}

void dfs_T(int v) {
	visit[v] = true;
	pre_T(v);
	for (int i = 0; i<Graph_T[v].size();i++) {
		if (visit[Graph_T[v][i]] == false) {
			dfs_T(Graph_T[v][i]);
		}
	}
	post_T(v);
}

int get_max_post() {
	int max_post = 0;
	for (int i = 1;i <= n;i++) {
		if (visit[i] == true) {
			continue;
		}

		if (post[i] > post[max_post]) {
			max_post = i;
		}
	}
	if (max_post == 0) {
		printf("모든 정점이 방문되었습니다");
	}
	return max_post;
}

void dfs(int v) {
	visit[v] = true;
	cc[v] = ccflag;
	for (int i = 0;i < Graph[v].size(); i++) {
		if (visit[Graph[v][i]] == 0) {
			dfs(Graph[v][i]);
		}
	}
}

int main() {
	int error;
	FILE* df;
	error = fopen_s(&df, "searchgraph.txt", "r");
	fscanf_s(df, "%d %d", &n, &m);

	for (int i = 1;i<=m;i++) {
		fscanf_s(df, "%d %d", &v, &u);
		Graph[v].push_back(u);
		Graph_T[u].push_back(v);
	}
	
	for (int i = 1;i<=n;i++) {
		sort(Graph[i].begin(), Graph[i].end());
		sort(Graph_T[i].begin(), Graph_T[i].end());
	}

	for (int i = 1;i<=n;i++) {
		if (visit[i] == 0) {
			dfs_T(i);
		}
	}

	for (int i = 1; i <= n; i++) {
		visit[i] = false;
	}

	for (int i = 1;i <= n;i++) {
		int max_post = get_max_post();
		if (max_post ==0 ) {
			break;
		}
		dfs(max_post);

		for (int j = 1;j <= n;j++) {
			if (cc[j] == ccflag) {
				printf("%d, ", j);
			}
		}
		printf("\n");
		ccflag ++ ;
	}

	return 0;
}