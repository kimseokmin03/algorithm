#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int n, m;
vector<pair<int, int>> graph[10001];
int visit[10001];

void prim() {
	vector<pair<int, int>> mcst;
	vector<int> U;
	priority_queue <pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>>pq;

	for (int i = 1;i <= n;i++) {
		visit[i] = 0;
	}
	int u, v, w;
	u = 1;
	U.push_back(u);
	visit[u] = 1;
	for (int i = 0;i < graph[u].size();i++) {
		v = graph[u][i].first;
		pq.push(make_pair(graph[u][i].second, make_pair(u, v)));
	}

	int no_mcst = 0;
	while (U.size() < n) {
		u = pq.top().second.first;
		v = pq.top().second.second;
		pq.pop();

		if (pq.empty()) {
			no_mcst = 0;
			break;
		}

		if (visit[u] == 0 || visit[v] == 1) {
			continue;
		}

		mcst.push_back(make_pair(u, v));
		U.push_back(v);
		visit[v] = 1;

		for (int i = 0; i < graph[v].size();i++) {
			u = graph[v][i].first;
			w = graph[v][i].second;
			if (visit[u] == 1) {
				continue;
			}
			pq.push(make_pair(w, make_pair(v, u)));
		}
	}

	if (no_mcst) {
		printf("No MCST\n");
	}
	else {
		for (int i = 0;i < mcst.size();i++) {
			printf("<%d, %d>\n", mcst[i].first, mcst[i].second);
		}
	}
}

int main() {
	FILE* fp;
	fopen_s(&fp, "prim_input.txt", "r+t");
	int tc, u, v, w;
	fscanf(fp, "%d", &tc);
	for (int t = 0;t < tc;t++) {
		fscanf(fp, "%d %d", &n, &m);
		for (int i = 1; i <= m;i++) {
			fscanf(fp, "%d %d %d", &u, &v, &w);
			graph[u].push_back(make_pair(v, w));
			graph[v].push_back(make_pair(u, w));
		}
		printf("%d\n", tc);
		prim();
	}
	fclose(fp);
	return 0;
}