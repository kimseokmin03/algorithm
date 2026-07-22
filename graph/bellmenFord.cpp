#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
vector<pair<int, int>> graph[10001];
int dist[10001];
int pre[10001];

void bellman_ford(int s){
    for(int i = 1; i<=n;i++){
        pre[i]=-1;
        dist[i]=INFINITY;
    }

    pre[0]=-1;
    dist[s]=0;

    int u,v,luv;
    for(int i = 1;i<n;i++){
        for(u = 1;u<=n;u++){
            for(int k = 0;k<graph[u].size();k++){
                v = graph[u][k].first;
                luv = graph[u][k].second;

                if(dist[u]!=INFINITY && dist[v] > dist[u]+luv){
                    dist[v]=dist[u]+luv;
                    pre[v]=u;
                }
            }
        }
    }
    for(int u =1;u<=n;u++){
        for(int k =0;k<graph[u].size();k++){
            v = graph[u][k].first;
            luv = graph[u][k].second;

            if(dist[u]!=INFINITY&&dist[v]>dist[u]+luv){
                printf("에러");
            }
        }
    }
}

int main(){
    int u, v, w, tc;
    pair<int, int> p;
    FILE* fp;
    fopen_s(&fp, "input.txt", "r+t");
    for (int j = 0; j < tc; j++) {
        fscanf_s(fp, "%d %d", &n, &m);
        for (int i = 1; i <= n; i++){
            graph[i].clear();
        }
    }

    for (int i = 1; i <= m; i++) {
        fscanf_s(fp, "%d %d %d", &u, &v, &w);
        graph[u].push_back(make_pair(v, w));
    }
    for (int i = 1; i <= n; i++){
        sort(graph[i].begin(), graph[i].end());
    }
    
    bellman_ford (1);
}