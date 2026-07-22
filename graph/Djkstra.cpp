#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int total_vertex, total_edge;
vector<pair<int, int>> graph[10001];
int dist[10001], pre[10001];
bool visit[10001];

void dijkstra(int s) {
	priority_queue<pair<int, int>> pq;

	for (int i = 0;i <= total_vertex;i++) {
		dist[i] = 1000000;
		pre[i] = -1;
		visit[i] = false;
	}
	dist[s] = 0;

	int w, lvw;
	pq.push(make_pair(0, s));
	//for (int i = 1;i <= total_vertex;i++) {
	//	pq.push(make_pair(-dist[i], i));
	//}

	while (!pq.empty()) {
		int v = pq.top().second;
		pq.pop();
		if (visit[v] == 1) {
			continue;
		}
		visit[v] = 1;

		for (int i = 0; i < graph[v].size();i++) {
			w = graph[v][i].first;
			lvw = graph[v][i].second;

			if (dist[w] > dist[v] + lvw) {
				dist[w] = dist[v] + lvw;
				pre[w] = v;
				pq.push(make_pair(-dist[w], w));
			}
		}
	}
}

void print_path(int n) {
	if (pre[n] != -1) {
		print_path(pre[n]);
		printf("->");
	}
	printf("%d", n);
}

int main() {
	FILE* df;
	int u, v, w;
	int error = fopen_s(&df, "searchgraph_weighted.txt","r");
	fscanf_s(df, "%d %d", &total_vertex, &total_edge);

	for (int i = 1; i <= total_edge;i++) {
		fscanf_s(df, "%d %d %d", &u, &v, &w);
		graph[u].push_back(make_pair(v, w));
	}
	fclose(df);

	for (int i = 1;i <= total_vertex;i++) {
		sort(graph[i].begin(), graph[i].end());
	}

	int input = 1;
	dijkstra(input);

	for (int i = 1;i <= total_vertex;i++) {
		print_path(i);
		printf("\n");
	}
	return 0;

}