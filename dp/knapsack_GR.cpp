#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <utility>
using namespace std;
int n;
int M;
int p[100];
int w[100];
float x[100];

void knapsack(){
    for(int i =0 ; i<n;i++){
        x[i]=0.0f;
    }

    priority_queue<pair<float,int>> myq;

    for(int i =0;i<n;i++){
        myq.push(make_pair((float)p[i] / (float)w[i], i));
    }
    int idx;
    int capacity = M;

    while(!myq.empty()){
        if(capacity ==0){
            break;
        }
        idx = myq.top().second;
        myq.pop();

        if(capacity>=w[idx]){
            x[idx]=1;
            capacity = capacity - w[idx];
        }
        else{
            x[idx]=(float) capacity/(float) w[idx];
            capacity=0;
        }
    }
}

int main() {
    FILE* fp;
    fopen_s(&fp, "input.txt", "r+t");
    int tc;
    fscanf_s(fp, "%d", &tc);
    for (int t = 0; t < tc; t++) {
        fscanf_s(fp, "%d", &n);
        fscanf_s(fp, "%d", &M);
        for (int i = 0; i < n; i++){
            fscanf_s(fp, "%d %d", &p[i], &w[i]);
        }
        knapsack();
    }
    fclose(fp);
    return 0;
}