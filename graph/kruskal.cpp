#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

int n, m;
vector <pair<int, pair<int, int>>> edges;

class UnionFind {
	vector<int> parent, rank;
	
public:
	UnionFind(int n) {
		parent.resize(n + 1);
		rank.resize(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	bool unit(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);
		if (rootX == rootY) { return false; }

		if (rank[rootX] < rank[rootY]) {
			parent[rootX] = rootY;
		}
		else if (rank[rootX] > rank[rootY]) {
			parent[rootY] = rootX;
		}
		else {
			parent[rootY] = rootX;
			rank[rootX]++;
		}
		return true;
	}
};

void kruskal() {
	vector<pair<int, int>> mcst;
	priority_queue < pair<int, pair<int, int>>,
		vector<pair<int, pair<int, int>>>, greater<>> pq;
	UnionFind uf(n);

	for (int i = 0; i < m; i++) {
		pq.push(edges[i]);
	}

	int u, v, w ;
	while (!pq.empty() && mcst.size() < n - 1) {
		w = pq.top().first;
		u = pq.top().second.first;
		v = pq.top().second.second;
		pq.pop();

		if (uf.find(u) != uf.find(v)) {
			mcst.push_back(make_pair(u, v));
			uf.unit(u, v);
		}
	}
	
	if (mcst.size() < n - 1) {
		printf("No MCST\n");
		return;
	}

	for (int i = 0; i < mcst.size(); i++) {
		/*printf("<%d, %d>\n", mcst[i].first, mcst[i].second);*/
		printf("<%c, %c>\n", mcst[i].first + 'A' - 1, mcst[i].second + 'A' - 1);
	}

}

int main() {
	FILE* fp;
	fopen_s(&fp, "kruskal_input.txt", "r + t");
	int tc, u, v, w ;
	fscanf(fp, "%d", &tc);
	edges.clear();
	for (int t = 0; t < tc; t++) {
		fscanf(fp, "%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			fscanf(fp, "%d %d %d", &u, &v, &w);
			edges.push_back(make_pair(w,make_pair(u, v)));
		}
		kruskal();
	}
	fclose(fp);
	return 0;
}

